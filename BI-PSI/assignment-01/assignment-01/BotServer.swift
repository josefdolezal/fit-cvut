//
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
}