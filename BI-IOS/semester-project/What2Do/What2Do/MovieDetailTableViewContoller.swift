import Foundation
import UIKit
import SVProgressHUD

struct Movie {
    var name: String
    var duration: String
    var language: String
    var startsIn: String
    
    init(name: String, duration: String, language: String, startsIn: String) {
        self.name = name
        self.duration = duration
        self.language = language
        self.startsIn = startsIn
    }
}

class MovieDetailTableViewContoller: UITableViewController {
    var movies = [[Movie]]()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        SVProgressHUD.show()
    }
    
    func dataLoaded(details: ServiceDetails) {
        self.parseDetails(details)
        self.tableView.reloadData()
        
        SVProgressHUD.dismiss()
    }
    
    private func parseDetails(details: ServiceDetails) {
        guard let movies = details.data?.array else {
            return
        }
        
        let dateNow = NSDate()
        
        for movie in movies {
            let name = movie["name"].stringValue
            let duration = movie["duration"].stringValue
            let language = movie["language"].stringValue
            
            var group = [Movie]()
            
            guard let showtimes = movie["showtimes"].array else {
                break
            }
            
            for showtime in showtimes {
                let time = showtime.stringValue.toTimeWithFormat("HH:mm:ss")
                let components = dateNow.timeDelta(time)
                
                if dateNow.timeDelta(time, lessThan: 40) {
                    group.append(Movie(
                        name: name,
                        duration: duration,
                        language: language,
                        startsIn: "\(components.hours * 60 + components.minutes)"
                    ))
                }
            }
            
            if(group.count > 0) {
                self.movies.append(group)
            }
        }
    }
    
    override func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        if(self.movies.count == 0) {
            let cell = tableView.dequeueReusableCellWithIdentifier("emptyCell", forIndexPath: indexPath)
            return cell
        }
        
        let cell = tableView.dequeueReusableCellWithIdentifier("movieDetailCell", forIndexPath: indexPath) as! MovieTableCell
        let movie = self.movies[indexPath.section][indexPath.row]
        
        cell.name = movie.name
        cell.startsIn = movie.startsIn
        cell.describeMovie(language: movie.language, duration: movie.duration)
        
        return cell
    }
    
    override func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return self.movies.count == 0 ? 1 : self.movies[section].count
    }
    
    override func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return self.movies.count == 0 ? 1 : self.movies.count
    }
    
    override func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return movies.count == 0 ? nil : "Movie: \(movies[section][0].name)"
    }
}