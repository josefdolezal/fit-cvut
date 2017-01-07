import Foundation


let server = BotServer(atPort: 4040)

Logger.start("server", description: "Starting server..")

server.run(maxConnections: 10) { descriptor in
    let controller = BotController(descriptor: descriptor)
    
    print("Starting connection at \(descriptor)")
    controller.listen()
    print("Connection at \(descriptor) closed")
}

Logger.stop("server")