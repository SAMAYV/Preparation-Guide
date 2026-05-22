from abc import ABC, abstractmethod

# The interface of a remote service.
# SERVICE INTERFACE
class ThirdPartyYouTubeLib(ABC):
    @abstractmethod
    def listVideos(self) -> list[str]:
        pass
    
    @abstractmethod
    def getVideoInfo(self, id) -> str:
        pass
    
    @abstractmethod
    def downloadVideo(self, id):
        pass


# The concrete implementation of a service connector. Methods of this class can request information from YouTube. The speed
# of the request depends on a user's internet connection as well as YouTube's. The application will slow down if a lot of
# requests are fired at the same time, even if they all request the same information.
# SERVICE
class ThirdPartyYouTubeClass(ThirdPartyYouTubeLib):
    def listVideos(self):
        # Send an API request to YouTube.
        print("Sending API request to YouTube for video list...")
        return ["Video1", "Video2", "Video3"]
    
    def getVideoInfo(self, id):
        # Get metadata about some video.
        print(f"Fetching metadata for video {id} from YouTube...")
        return f"Video info for {id}"
    
    def downloadVideo(self, id):
        # Download a video file from YouTube.
        print(f"Downloading video {id} from YouTube...")


# To save some bandwidth, we can cache request results and keep them for some time. But it may be impossible to put such code
# directly into the service class. For example, it could have been provided as part of a third party library and/or defined
# as `final`. That's why we put the caching code into a new proxy class which implements the same interface as the
# service class. It delegates to the service object only when the real requests have to be sent.
# PROXY
class CachedYouTubeClass(ThirdPartyYouTubeLib):
    def __init__(self, service: ThirdPartyYouTubeLib):
        self.service = service
        self.listCache = None
        self.videoCache = {}
        self.needReset = False
    
    def listVideos(self):
        if self.listCache is None or self.needReset:
            self.listCache = self.service.listVideos()
        else:
            print("Returning cached video list")
        return self.listCache
    
    def getVideoInfo(self, id):
        if id not in self.videoCache or self.needReset:
            self.videoCache[id] = self.service.getVideoInfo(id)
        else:
            print(f"Returning cached info for video {id}")
        return self.videoCache[id]
    
    def downloadVideo(self, id):
        if not self.downloadExists(id) or self.needReset:
            self.service.downloadVideo(id)
        else:
            print(f"Video {id} already downloaded")
    
    def downloadExists(self, id):
        return False


# The GUI class, which used to work directly with a service object, stays unchanged as long as it works with the service
# object through an interface. We can safely pass a proxy object instead of a real service object since they both
# implement the same interface.
# CLIENT
class YouTubeManager:
    def __init__(self, service: ThirdPartyYouTubeLib):
        self.service = service
    
    def renderVideoPage(self, id):
        info = self.service.getVideoInfo(id)
        # Render the video page.
        print(f"Rendering video page: {info}")
    
    def renderListPanel(self):
        list = self.service.listVideos()
        # Render the list of video thumbnails.
        print(f"Rendering list panel: {list}")
    
    def reactOnUserInput(self):
        self.renderVideoPage("video123")
        self.renderListPanel()


# The application can configure proxies on the fly.
class Application:
    def init(self):
        aYouTubeProxy = CachedYouTubeClass(ThirdPartyYouTubeClass())
        manager = YouTubeManager(aYouTubeProxy)
        manager.reactOnUserInput()
        
        print("\n--- Second request (cached) ---\n")
        manager.reactOnUserInput()


if __name__ == "__main__":
    app = Application()
    app.init()
