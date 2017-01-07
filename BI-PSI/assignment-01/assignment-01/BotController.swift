//
//  BotController.swift
//  assignment-01
//
//  Created by Josef Dolezal on 30/04/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation

// MARK: - Bot Controller

class BotController {
    private let descriptor : Int32
    
    private var descriptorClosed = false
    private var bot : Bot
    
    private var timeoutConnected : timeval
    private var timeoutRecharging: timeval
    private var sockets : fd_set
    
    init(descriptor: Int32) {
        self.descriptor = descriptor
        self.timeoutConnected = timeval(tv_sec: BotServer.connectionTimeout, tv_usec: 0)
        self.timeoutRecharging = timeval(tv_sec: BotServer.rechargingTimeout, tv_usec: 0)
        self.sockets = fd_set();
        self.bot = Bot()
    }
    
    func listen() -> RunResult {
        var messageForBot = [String]()
        var leftover = ""
        
        while true {
            let currentMessage = messageForBot.count != 0 ? messageForBot.removeAtIndex(0) : ""
            
            let (msg, statBot) = bot.message(currentMessage);
            
            if statBot == .CLOSE_IMMEDIATELY {
                return closeAndReturn(RunResult.CONNECTION_CLOSED)!
            }
            
            if statBot != .RECEIVE {
                sendCommand(msg.text)
            }
            
            if statBot == .CLOSE_WHEN_SENT {
                return closeAndReturn(RunResult.CONNECTION_CLOSED)!
            }
            
            if statBot == .TALK_AGAIN {
                messageForBot.insert("", atIndex: 0)
                continue
            }
            
            if(messageForBot.count > 0) {
                continue
            }
            
            let (rcv, statCmd) = receiveCommand(msg, leftover: leftover)
            
            if statCmd == .CLOSE_WHEN_SENT {
                sendCommand(rcv)
                closeAndReturn(RunResult.CONNECTION_CLOSED)
            }
            
            if statCmd != .CONNECTED {
                return closeAndReturn(statCmd)!
            }
            
            let components = rcv.componentsSeparatedByString("\r\n")
            
            for i in 0..<components.count {
                if i+1 == components.count {
                    leftover = components[i]
                    break
                }
                
                messageForBot.append(components[i])
            }
        }
    }
    
    private func sendCommand(command: String) -> RunResult {
        let buffer : [UInt8] = Array(command.utf8)
        
        if send(descriptor, buffer, buffer.count, 0) == -1 {
            return RunResult.CANNOT_SEND
        }
        
        return RunResult.CONNECTED
    }
    
    private func receiveCommand(type: Message, leftover: String = "") -> (message: String, status: RunResult) {
        var result = leftover
        
        repeat {
            let status = checkConnectionStatus()
            
            if status != .CONNECTED {
                return ("", status)
            }
            
            var buffer = [CChar](count: Communicator.socketBufferLength, repeatedValue: 0)
            
            if recv(descriptor, &buffer, Communicator.socketBufferLength, 0) <= 0 {
                return ("", RunResult.CONNECTION_CLOSED_BY_CLIENT)
            }
            
            result += String.fromCString(&buffer)!
            
            /* Possible leftover */
            if result.containsString("\r\n") {
                break
            }
            
            if type.responseLengthExceeded(result) {
                print("cont exxceed")
                print(type.maxResponseLen)
                print(type.text)
                print(result)
                print(result.characters.count)
                return (Communicator.syntaxError.text, RunResult.CLOSE_WHEN_SENT)
            }
            
        } while !result.hasSuffix("\r\n")
        
        return (result, RunResult.CONNECTED)
    }
    
        private func checkConnectionStatus() -> RunResult {
        BrigdeToC.FD_ZERO(&sockets)
        BrigdeToC.FD_SET(descriptor, set: &sockets)
        
        var timeout = bot.currentState == .RECHARGING ? timeoutRecharging : timeoutConnected
        
        let status = select(descriptor + 1, &sockets, nil, nil, &timeout)
        
        if(status < 0) {
            return closeAndReturn(RunResult.SELECT_DOES_NOT_WORK)!
        }
        
        if(!BrigdeToC.FD_ISSET(descriptor, set: &sockets)) {
            return closeAndReturn(RunResult.CONNECTION_TIMEOUT)!
        }
        
        return RunResult.CONNECTED
    }
    
    private func closeDescriptor() {
        if !descriptorClosed {
            close(descriptor)
            descriptorClosed = true
        }
    }
    
    private func closeAndReturn(stat: RunResult?) -> RunResult? {
        closeDescriptor()
        
        return stat
    }
}

// MARK: - Communicator

class Message {
    var text: String
    var maxResponseLen: Int
    
    init(_ text: String, maxLen: Int, suffixLen: Int = 2) {
        self.text = text
        maxResponseLen = maxLen - (maxLen < suffixLen ? 0 : suffixLen)
    }
    
    func responseLengthExceeded(response: String) -> Bool {
        let res = response.stringByRemovingSuffix("\r")
        
        if res.characters.count > maxResponseLen {
            return true
        }
        
        return false
    }
}

func ==(left: Message, right: Message) -> Bool {
    return left.text == right.text && left.maxResponseLen == right.maxResponseLen
}

class Communicator {
    internal static let empty = Message("", maxLen: 0)
    
    internal static let askLogin = Message("100 LOGIN\r\n", maxLen: 100)
    internal static let askPassword = Message("101 PASSWORD\r\n", maxLen: 7)
    internal static let loginFailed = Message("300 LOGIN FAILED\r\n", maxLen: 0)
    
    internal static let ok = Message("200 OK\r\n", maxLen: 0, suffixLen: 0)
    internal static let syntaxError = Message("301 SYNTAX ERROR\r\n", maxLen: 0)
    internal static let logicError = Message("302 LOGIC ERROR\r\n", maxLen: 0)
    
    internal static let move = Message("102 MOVE\r\n", maxLen: 12)
    internal static let turnLeft = Message("103 TURN LEFT\r\n", maxLen: 12)
    internal static let turnRight = Message("104 TURN RIGHT\r\n", maxLen: 12)
    internal static let getMessage = Message("105 GET MESSAGE\r\n", maxLen: 100)
    internal static let recharging = Message("RECHARGING", maxLen: 12)

    internal static let socketBufferLength = 512
    internal static let maxMessageLen = 98

    internal static let syntaxFullPower = "FULL POWER"
}