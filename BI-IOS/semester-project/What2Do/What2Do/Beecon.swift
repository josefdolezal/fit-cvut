import Alamofire
import SwiftyJSON

struct CampaignDetails {
    var name: String
    var uuid: String
    
    init(withName name: String, UUID: String) {
        self.name = name
        self.uuid = UUID
    }
}

struct Service {
    var name: String
    var major: String
    var minor: String
    
    init(withName name: String = "Unknown", major: String, minor: String) {
        self.name = name
        self.major = major
        self.minor = minor
    }
    
    func toDictionaryWithApp( appCode: String ) -> [String: String]{
        return [
            "app_code": appCode,
            "location": self.major,
            "service": self.minor
        ]
    }
}

struct ServiceDetails {
    var response: JSON
    var data: JSON?
    
    var service:Service
    
    init(withService service: Service, response: JSON) {
        self.service = service
        self.response = response
        self.data = response["data"]
    }
}

class Beecon {
    let apiUrl = "http://rawdesign.cz:8000"
    
    var appCode: String!
    
    init(withAppCode code: String) {
        self.appCode = code
    }
    
    func campaignInfo(completionHandler: (CampaignDetails) -> Void) {
        self.networkRequest(self.campaignUrl()) { json in
            guard let name = json["app"].string else {
                return
            }
            
            guard let uuid = json["uuid"].string else {
                return
            }
            
            completionHandler(CampaignDetails(withName: name, UUID: uuid))
        }
    }
    
    func callService(service: Service, completionHandle handler: (ServiceDetails) -> Void) {
        self.networkRequest(
                self.serviceUrl(true),
                parameters: service.toDictionaryWithApp(self.appCode))
        { json in
            guard let name = json["service"].string else {
                return
            }
            
            var serv = service
            serv.name = name
            
            handler( ServiceDetails(withService: serv, response: json))
        }
    }
    
    func listServices(completionHandler: (([Service]) -> Void)?) {
        self.networkRequest(self.serviceUrl()) { json in
            var services: [Service] = []
            
            for (_, sub):(String, JSON) in json["services"] {
                guard let name = sub["name"].string else {
                    continue
                }
                
                guard let major = sub["major"].string else {
                    continue
                }
                
                guard let minor = sub["minor"].string else {
                    continue
                }
                
                services.append(Service(withName: name, major: major, minor: minor))
            }
            
            completionHandler?(services)
        }
    }
    
    private func networkRequest(
        url: String,
        parameters: [String: AnyObject]? = nil,
        completionHandler: (JSON) -> Void)
    {
        Alamofire.request(.GET, url, parameters: parameters)
            .responseJSON { response in switch response.result {
            case .Success:
                guard let value = response.result.value else {
                    return
                }

                let json = JSON(value)
                completionHandler(json)
            case .Failure:
                break
            }
        }
    }
    
    private func campaignUrl() -> String {
        return "\(self.apiUrl)/campaigns/\(self.appCode)/info"
    }
    
    private func serviceUrl(singleService: Bool = false) -> String {
        let url = "\(self.apiUrl)/campaigns/"
        
        return singleService ?
            "\(url)" :
        "\(url)\(self.appCode)/services/"
    }
}