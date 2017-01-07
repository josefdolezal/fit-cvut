//
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
}