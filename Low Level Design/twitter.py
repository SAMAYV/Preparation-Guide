"""
LLD for Twitter

Entities being considered:
- User
- Tweet
- Feed
- Feed generation Strategy
- Twitter Application (?)

Basic Requirements:
1. User should be able to follow others
2. Should only be able to see tweets of users the user follows
3. Can let go of features like tweets on profile, interacting with tweets for now
"""
from abc import ABC, abstractmethod
import time


class FeedGenerationStrategy(ABC):
    @staticmethod
    @abstractmethod
    def update_feed(feed, tweet):
        pass

    @staticmethod
    @abstractmethod
    def refresh_feed(feed):
        pass


class ReverseChronoFeedGenerationStrategy(FeedGenerationStrategy):
    @staticmethod
    def update_feed(feed, tweet):
        # Adding the newest tweet at the top.
        feed.append(tweet)

    @staticmethod
    def refresh_feed(feed):
        feed.sort(key=lambda x: x.post_time, reverse=True)


class MostLikedFirstFeedGenerationStrategy(FeedGenerationStrategy):
    @staticmethod
    def update_feed(feed, tweet):
        # Adding the newest tweet at the bottom because it'll have 0 likes initially.
        feed.append(tweet)

    @staticmethod
    def refresh_feed(feed):
        feed.sort(key=lambda x: x.like_count, reverse=True)


class Tweet:
    tweet_id_counter = 1

    def __init__(self, content, user, post_time):
        self._tweet_id = self.tweet_id_counter
        self.content = content
        self.author = user
        self.post_time = post_time
        self.like_count = 0
        Tweet.tweet_id_counter += 1

    @property
    def id(self):
        return self._tweet_id

    def __repr__(self):
        return (f"ID: {self._tweet_id} \n {self.content} \n Liked by: {self.like_count}"
                f" \n Posted By: {self.author.username} at {self.post_time}")


class User:

    uid_counter = 1

    def __init__(self, name: str, feed_strategy):
        self.uid = User.uid_counter
        self._user_name = name
        self.followers = []
        self.following = []
        self.feed_generation_strategy = feed_strategy()
        self.feed = []
        self.user_tweets = []
        self.liked_tweets = []
        User.uid_counter += 1

    @property
    def username(self):
        return self._user_name

    def add_to_following(self, user):
        if user not in self.following:
            self.following.append(user)

    def add_to_followers(self, user):
        if user not in self.followers:
            self.followers.append(user)

    def follow(self, user):
        self.add_to_following(user)
        user.add_to_followers(self)

    def update_feed(self, tweet):
        self.feed_generation_strategy.update_feed(self.feed, tweet)

    def post_tweet(self, content):
        tweet = Tweet(content, self, time.time())
        self.user_tweets.append(tweet)
        for follower in self.followers:
            follower.update_feed(tweet)

    def show_feed(self):
        self.feed_generation_strategy.refresh_feed(self.feed)
        print(f"{self._user_name}'s Feed: ")
        for tweet in self.feed:
            print(tweet)
        print('--------------------------------------------------------')

    def like_tweet(self, tweet_id):
        for tweet in self.feed:
            if tweet_id == tweet.id and tweet_id not in self.liked_tweets:
                tweet.like_count += 1
                self.liked_tweets.append(tweet_id)

    def __str__(self):
        return ""


def main():
    Arpan = User('Arpan', ReverseChronoFeedGenerationStrategy)
    Moin = User('Moin', ReverseChronoFeedGenerationStrategy)
    Samay = User('Samay', ReverseChronoFeedGenerationStrategy)
    Shreyans = User('Sheyans', MostLikedFirstFeedGenerationStrategy)
    Harsh = User('Harsh', MostLikedFirstFeedGenerationStrategy)
    Chirag = User('Chirag', MostLikedFirstFeedGenerationStrategy)

    Arpan.follow(Moin)
    Arpan.follow(Samay)
    Arpan.follow(Shreyans)
    Arpan.follow(Harsh)
    Arpan.follow(Chirag)

    Moin.follow(Arpan)
    Moin.follow(Samay)

    Samay.follow(Arpan)
    Samay.follow(Moin)

    Shreyans.follow(Arpan)
    Shreyans.follow(Harsh)
    Shreyans.follow(Chirag)

    Harsh.follow(Arpan)
    Harsh.follow(Shreyans)
    Harsh.follow(Chirag)

    Chirag.follow(Shreyans)
    Chirag.follow(Harsh)
    Chirag.follow(Arpan)

    Arpan.post_tweet("Arpan's First Tweet")
    time.sleep(0.1)
    Moin.post_tweet("Moin's First Tweet")
    time.sleep(0.1)
    Shreyans.post_tweet("Shreyans's First Tweet")
    time.sleep(0.1)
    Arpan.post_tweet("Arpan's Second Tweet")
    time.sleep(0.1)
    Arpan.post_tweet("Arpan's third Tweet")
    time.sleep(0.1)
    Harsh.post_tweet("Harsh's First Tweet")
    time.sleep(0.1)
    Samay.post_tweet("Samay's First Tweet")
    time.sleep(0.1)
    Moin.post_tweet("Moin's Second Tweet")
    time.sleep(0.1)
    Harsh.post_tweet("Harsh's Second Tweet")
    time.sleep(0.1)
    Chirag.post_tweet("Chirag's First Tweet")

    Arpan.show_feed()
    Chirag.show_feed()

    Moin.like_tweet(1)
    Moin.like_tweet(4)

    Arpan.like_tweet(3)
    Arpan.like_tweet(9)

    Shreyans.like_tweet(1)
    Shreyans.like_tweet(4)
    Shreyans.like_tweet(9)

    Harsh.like_tweet(1)
    Harsh.like_tweet(4)

    Chirag.like_tweet(1)

    Arpan.show_feed()
    Chirag.show_feed()


if __name__ == "__main__":
    main()
