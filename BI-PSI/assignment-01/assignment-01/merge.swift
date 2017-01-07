//
//  CBridge.swift
//  assignment-01
//
//  Created by Josef Dolezal on 22/04/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation

extension sockaddr_in {
    mutating func asSockAddr() -> UnsafeMutablePointer<sockaddr> {
        return withUnsafePointer(&self) { UnsafeMutablePointer<sockaddr>($0) }
    }
    
    func sockLen() -> socklen_t {
        return socklen_t(sizeofValue(self))
    }
    
    static func shortInit(addressFamily: Int32, port: Int, socketAddress: UInt32) -> sockaddr_in {
        var address = sockaddr_in()
        address.sin_family = sa_family_t(addressFamily)
        address.sin_port = UInt16(port).bigEndian
        address.sin_addr.s_addr = socketAddress
        
        return address
    }
}

struct BrigdeToC {
    internal static let ADDR_ANY = UInt32(0x00000000)
    
    internal static func FD_ZERO(inout set: fd_set) {
        set.fds_bits = (0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    }
    
    internal static func FD_SET(fd: Int32, inout set: fd_set) {
        let intOffset = Int(fd / 32)
        let bitOffset = fd % 32
        let mask = 1 << bitOffset
        switch intOffset {
        case 0: set.fds_bits.0 = set.fds_bits.0 | mask
        case 1: set.fds_bits.1 = set.fds_bits.1 | mask
        case 2: set.fds_bits.2 = set.fds_bits.2 | mask
        case 3: set.fds_bits.3 = set.fds_bits.3 | mask
        case 4: set.fds_bits.4 = set.fds_bits.4 | mask
        case 5: set.fds_bits.5 = set.fds_bits.5 | mask
        case 6: set.fds_bits.6 = set.fds_bits.6 | mask
        case 7: set.fds_bits.7 = set.fds_bits.7 | mask
        case 8: set.fds_bits.8 = set.fds_bits.8 | mask
        case 9: set.fds_bits.9 = set.fds_bits.9 | mask
        case 10: set.fds_bits.10 = set.fds_bits.10 | mask
        case 11: set.fds_bits.11 = set.fds_bits.11 | mask
        case 12: set.fds_bits.12 = set.fds_bits.12 | mask
        case 13: set.fds_bits.13 = set.fds_bits.13 | mask
        case 14: set.fds_bits.14 = set.fds_bits.14 | mask
        case 15: set.fds_bits.15 = set.fds_bits.15 | mask
        case 16: set.fds_bits.16 = set.fds_bits.16 | mask
        case 17: set.fds_bits.17 = set.fds_bits.17 | mask
        case 18: set.fds_bits.18 = set.fds_bits.18 | mask
        case 19: set.fds_bits.19 = set.fds_bits.19 | mask
        case 20: set.fds_bits.20 = set.fds_bits.20 | mask
        case 21: set.fds_bits.21 = set.fds_bits.21 | mask
        case 22: set.fds_bits.22 = set.fds_bits.22 | mask
        case 23: set.fds_bits.23 = set.fds_bits.23 | mask
        case 24: set.fds_bits.24 = set.fds_bits.24 | mask
        case 25: set.fds_bits.25 = set.fds_bits.25 | mask
        case 26: set.fds_bits.26 = set.fds_bits.26 | mask
        case 27: set.fds_bits.27 = set.fds_bits.27 | mask
        case 28: set.fds_bits.28 = set.fds_bits.28 | mask
        case 29: set.fds_bits.29 = set.fds_bits.29 | mask
        case 30: set.fds_bits.30 = set.fds_bits.30 | mask
        case 31: set.fds_bits.31 = set.fds_bits.31 | mask
        default: break
        }
    }
    
    internal static func FD_CLR(fd: Int32, inout set: fd_set) {
        let intOffset = Int(fd / 32)
        let bitOffset = fd % 32
        let mask = ~(1 << bitOffset)
        switch intOffset {
        case 0: set.fds_bits.0 = set.fds_bits.0 & mask
        case 1: set.fds_bits.1 = set.fds_bits.1 & mask
        case 2: set.fds_bits.2 = set.fds_bits.2 & mask
        case 3: set.fds_bits.3 = set.fds_bits.3 & mask
        case 4: set.fds_bits.4 = set.fds_bits.4 & mask
        case 5: set.fds_bits.5 = set.fds_bits.5 & mask
        case 6: set.fds_bits.6 = set.fds_bits.6 & mask
        case 7: set.fds_bits.7 = set.fds_bits.7 & mask
        case 8: set.fds_bits.8 = set.fds_bits.8 & mask
        case 9: set.fds_bits.9 = set.fds_bits.9 & mask
        case 10: set.fds_bits.10 = set.fds_bits.10 & mask
        case 11: set.fds_bits.11 = set.fds_bits.11 & mask
        case 12: set.fds_bits.12 = set.fds_bits.12 & mask
        case 13: set.fds_bits.13 = set.fds_bits.13 & mask
        case 14: set.fds_bits.14 = set.fds_bits.14 & mask
        case 15: set.fds_bits.15 = set.fds_bits.15 & mask
        case 16: set.fds_bits.16 = set.fds_bits.16 & mask
        case 17: set.fds_bits.17 = set.fds_bits.17 & mask
        case 18: set.fds_bits.18 = set.fds_bits.18 & mask
        case 19: set.fds_bits.19 = set.fds_bits.19 & mask
        case 20: set.fds_bits.20 = set.fds_bits.20 & mask
        case 21: set.fds_bits.21 = set.fds_bits.21 & mask
        case 22: set.fds_bits.22 = set.fds_bits.22 & mask
        case 23: set.fds_bits.23 = set.fds_bits.23 & mask
        case 24: set.fds_bits.24 = set.fds_bits.24 & mask
        case 25: set.fds_bits.25 = set.fds_bits.25 & mask
        case 26: set.fds_bits.26 = set.fds_bits.26 & mask
        case 27: set.fds_bits.27 = set.fds_bits.27 & mask
        case 28: set.fds_bits.28 = set.fds_bits.28 & mask
        case 29: set.fds_bits.29 = set.fds_bits.29 & mask
        case 30: set.fds_bits.30 = set.fds_bits.30 & mask
        case 31: set.fds_bits.31 = set.fds_bits.31 & mask
        default: break
        }
    }
    
    internal static func FD_ISSET(fd: Int32, inout set: fd_set) -> Bool {
        let intOffset = Int(fd / 32)
        let bitOffset = fd % 32
        let mask = 1 << bitOffset
        switch intOffset {
        case 0: return set.fds_bits.0 & mask != 0
        case 1: return set.fds_bits.1 & mask != 0
        case 2: return set.fds_bits.2 & mask != 0
        case 3: return set.fds_bits.3 & mask != 0
        case 4: return set.fds_bits.4 & mask != 0
        case 5: return set.fds_bits.5 & mask != 0
        case 6: return set.fds_bits.6 & mask != 0
        case 7: return set.fds_bits.7 & mask != 0
        case 8: return set.fds_bits.8 & mask != 0
        case 9: return set.fds_bits.9 & mask != 0
        case 10: return set.fds_bits.10 & mask != 0
        case 11: return set.fds_bits.11 & mask != 0
        case 12: return set.fds_bits.12 & mask != 0
        case 13: return set.fds_bits.13 & mask != 0
        case 14: return set.fds_bits.14 & mask != 0
        case 15: return set.fds_bits.15 & mask != 0
        case 16: return set.fds_bits.16 & mask != 0
        case 17: return set.fds_bits.17 & mask != 0
        case 18: return set.fds_bits.18 & mask != 0
        case 19: return set.fds_bits.19 & mask != 0
        case 20: return set.fds_bits.20 & mask != 0
        case 21: return set.fds_bits.21 & mask != 0
        case 22: return set.fds_bits.22 & mask != 0
        case 23: return set.fds_bits.23 & mask != 0
        case 24: return set.fds_bits.24 & mask != 0
        case 25: return set.fds_bits.25 & mask != 0
        case 26: return set.fds_bits.26 & mask != 0
        case 27: return set.fds_bits.27 & mask != 0
        case 28: return set.fds_bits.28 & mask != 0
        case 29: return set.fds_bits.29 & mask != 0
        case 30: return set.fds_bits.30 & mask != 0
        case 31: return set.fds_bits.31 & mask != 0
        default: return false
        }
        
    }
}//
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
}//
//  Bot.swift
//  assignment-01
//
//  Created by Josef Dolezal on 30/04/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation

// MARK: Bot
class Bot {
    enum Orientation {
        case TOP
        case RIGHT
        case BOTTOM
        case LEFT
        case UNKNOWN
    }
    
    struct Position {
        var X : Int?
        var Y : Int?
        
        func isSet() -> Bool {
            return X != nil && Y != nil
        }
        
        mutating func moveTo(x: Int, y: Int) {
            X = x
            Y = y
        }
        
        mutating func moveTo(position: Position) {
            X = position.X
            Y = position.Y
        }
        
        func eq(x: Int, y: Int) -> Bool {
            return x == X && y == Y
        }
    }
    
    var currentState : BotState { get { return state } }
    
    private var orientation = Orientation.UNKNOWN
    private var state = BotState.WAITING_FOR_USERNAME
    private var lastCommand : Message?
    
    private var rechargeBackup : (message: Message, state: BotState)?
    
    private var actualPosition = Position()
    private var username : Int = -1
    
    
    func message(client: String) -> (message: Message, status: RunResult) {
        var status = RunResult.CONNECTED
        var response = Communicator.ok
        
        print(client + "\n")
        
        if client.characters.count > Communicator.maxMessageLen {
            print("synt eerrrr count")
            return (Communicator.syntaxError, RunResult.CLOSE_WHEN_SENT)
        }
        
        if client == Communicator.recharging.text {
            state = .RECHARGING
            
            return (Communicator.recharging, RunResult.RECEIVE)
        }
        
        switch state {
        case .WAITING_FOR_USERNAME:
            state = .WAITING_FOR_PASSWORD
            response = Communicator.askLogin
            
        case .WAITING_FOR_PASSWORD:
            username = client.sumElements()
            state = .SHOULD_AUTH
            response = Communicator.askPassword
            
        case .SHOULD_AUTH:
            if client != String(username) {
                response = Communicator.loginFailed
                status = .CLOSE_WHEN_SENT
                break
            }
            
            response = Communicator.ok
            status = .TALK_AGAIN
            state = .SHOULD_MOVE
            
        case .SHOULD_MOVE:
            response = Communicator.move
            state = .MOVING
            
        case .MOVING:
            guard let pos = extractCoordinates(client) else {
                status = .CLOSE_WHEN_SENT
                response = Communicator.syntaxError
                break
            }
            
            if pos.eq(0, y: 0) {
                (response, status) = getMessage()
                break
            }
            
            if (orientation == .UNKNOWN && !actualPosition.isSet()) {
                response = Communicator.move
                actualPosition.moveTo(pos)
                break
            }
            
            if (pos == actualPosition) && lastCommand! == Communicator.move {
                response = lastCommand!
                break
            }
            
            if orientation == .UNKNOWN {
                determineOrientation(pos)
            }
            
            (response, status) = shortestWay(pos)
            
        case .DONE:
            response = Communicator.ok
            status = .CLOSE_WHEN_SENT
            
        case .RECHARGING:
            if client != Communicator.syntaxFullPower {
                response = Communicator.logicError
                status = .CLOSE_WHEN_SENT
                break
            }
            
            state = rechargeBackup!.state
            status = .RECEIVE
            response = rechargeBackup!.message
        }
        
        lastCommand = response
        rechargeBackup = (response, state)
        return (response, status)
    }
    
    private func determineOrientation(newPosition: Position) {
        let xDiff = actualPosition.X! < newPosition.X!
        let yDiff = actualPosition.Y! < newPosition.Y!
        
        // Right or Left
        if actualPosition.X! - newPosition.X! != 0 {
            orientation = xDiff ? .RIGHT : .LEFT
            return
        }
        
        orientation = yDiff ? .TOP : .BOTTOM
    
    }
    
    private func getMessage() -> (message: Message, status: RunResult) {
        state = .DONE
        return (Communicator.getMessage, RunResult.CONNECTED)
    }
    
    private func shortestWay(pos: Position) -> (message: Message, status: RunResult) {
        let res = RunResult.CONNECTED
        actualPosition.moveTo(pos)
        
        if actualPosition.X != 0 {
            if actualPosition.X < 0 {
                return orientation == .RIGHT ? (Communicator.move, res) : (rotateRight(), res)
            }
            
            return orientation == .LEFT ? (Communicator.move, res) : (rotateRight(), res)
        }
        
        if actualPosition.Y < 0 {
            return orientation == .TOP ? (Communicator.move, res) : (rotateRight(), res)
        }
        
        return orientation == .BOTTOM ? (Communicator.move, res) : (rotateRight(), res)
    }
    
    private func rotateRight() -> Message {
        var orientation = Orientation.UNKNOWN
        
        switch self.orientation {
        case .TOP:
            orientation = .RIGHT
        case .RIGHT:
            orientation = .BOTTOM
        case .BOTTOM:
            orientation = .LEFT
        case .LEFT:
            orientation = .TOP
        default:
            break
        }
        
        self.orientation = orientation
        
        return Communicator.turnRight
    }
    
    private func extractCoordinates(message: String) -> Position? {
        let coords = message.componentsSeparatedByString(" ")
        
        guard coords.count == 3 else {
            return nil
        }
        
        guard coords[0] == "OK" else {
            return nil
        }
        
        if let coordX = Int(coords[1]) {
            if let coordY = Int(coords[2]) {
                return Position(X: coordX, Y: coordY)
            }
        }
        
        return nil
    }
}

// MARK: - Bot State

enum BotState {
    case WAITING_FOR_USERNAME
    case WAITING_FOR_PASSWORD
    case SHOULD_AUTH
    case SHOULD_MOVE
    case MOVING
    case DONE
    case RECHARGING
}

// MARK: - Operator overloads

func ==(left: Bot.Position, right: Bot.Position) -> Bool {
    return left.eq(right.X!, y: right.Y!)
}//
//  BotServer.swift
//  assignment-01
//
//  Created by Josef Dolezal on 30/04/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation

// MARK: BotServer

class BotServer {
    internal static let connectionTimeout = 1
    internal static let rechargingTimeout = 5
    
    private let serverSocket : Int32
    
    private var callback : ((Int32)->())?
    private var maxConnections : Int32!
    private var address : sockaddr_in
    
    private var socketClosed = false
    
    init(atPort port : Int) {
        serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)
        address = sockaddr_in.shortInit(AF_INET, port: port, socketAddress: BrigdeToC.ADDR_ANY)
    }
    
    func run(maxConnections connections: Int32, connectionCallback: (Int32)->()) -> RunResult {
        maxConnections = connections
        callback = connectionCallback
        
        if bind(serverSocket, address.asSockAddr(), address.sockLen()) < 0 {
            return closeSocketOnError(RunResult.CANNOT_BIND)
        }
        
        if listen(serverSocket, 10) < 0 {
            return closeSocketOnError(RunResult.CANNOT_LISTEN)
        }
        
        connectionLoop()
        
        return RunResult.CONNECTION_CLOSED
    }
    
    private func connectionLoop() -> RunResult {
        var remoteAddress = sockaddr_in();
        var remoteAddressLen = socklen_t();
        
        while true {
            let requestDescriptor = accept(serverSocket, remoteAddress.asSockAddr(), &remoteAddressLen)
            
            if requestDescriptor < 0 {
                return closeSocketOnError(RunResult.CANNOT_ACCEPT)
            }
            
            dispatch_async(dispatch_get_global_queue(QOS_CLASS_USER_INITIATED, 0)) {
                self.callback?(requestDescriptor)
            }
        }
    }
    
    private func closeSocketOnError(error: RunResult) -> RunResult {
        close(serverSocket)
        socketClosed = true
        return error
    }
    
    deinit {
        if !socketClosed {
            close(serverSocket)
        }
    }
}

// MARK: - Server states

enum RunResult {
    case CANNOT_BIND
    case CANNOT_LISTEN
    case CANNOT_ACCEPT
    case CANNOT_SEND
    case CLOSE_IMMEDIATELY
    case CLOSE_WHEN_SENT
    case TALK_AGAIN
    case SELECT_DOES_NOT_WORK
    case CONNECTION_TIMEOUT
    case CONNECTION_CLOSED_BY_CLIENT
    case CONNECTION_CLOSED
    case CONNECTED
    case RECEIVE
}//
//  Logger.swift
//  assignment-01
//
//  Created by Josef Dolezal on 30/04/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation
import QuartzCore

class Logger {
    private static var logs = [String: CFTimeInterval]()
    
    static func start(id: String, description: String = "") {
        logs[id] = CACurrentMediaTime()
        print("[Start:\(id)] \(description)")
    }
    
    static func stop(id: String) {
        if let start = logs[id] {
            logs.removeValueForKey(id)
            print("[Stop:\(id) ] End in \(CACurrentMediaTime() - start)")
        }
    }
}//
//  StringExtensions.swift
//  assignment-01
//
//  Created by Josef Dolezal on 01/05/16.
//  Copyright © 2016 Josef Dolezal. All rights reserved.
//

import Foundation

extension String {
    func sumElements() -> Int {
        return Array(self.utf8).reduce(0) { Int($0) + Int($1) }
    }
    
    func stringByRemovingSuffix(suffix: String) -> String {
        if self.hasSuffix(suffix) {
            return self.substringToIndex(self.endIndex.advancedBy(-1*suffix.characters.count))
        }
        
        return self
    }
}import Foundation


let server = BotServer(atPort: 4040)

Logger.start("server", description: "Starting server..")

server.run(maxConnections: 10) { descriptor in
    let controller = BotController(descriptor: descriptor)
    
    print("Starting connection at \(descriptor)")
    controller.listen()
    print("Connection at \(descriptor) closed")
}

Logger.stop("server")