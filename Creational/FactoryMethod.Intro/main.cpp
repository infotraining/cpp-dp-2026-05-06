#include "factory.hpp"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

namespace StronglyCoupled
{
    class MusicApp
    {
    public:
        MusicApp() = default;

        void play(const std::string& track_title)
        {
            // creation of product
            SpotifyService music_service("spotify_user", "rjdaslf276%2", 45);

            std::optional<Track> track = music_service.get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto& note : *track)
                    std::cout << note << ".";
                std::cout << "|\n";
            }
            else
            {
                std::cout << "Track not found!\n";
            }
        }
    };
}

class MusicApp
{
    std::shared_ptr<MusicServiceCreator> music_service_creator_;

public:
    MusicApp(std::shared_ptr<MusicServiceCreator> music_service_creator)
        : music_service_creator_(music_service_creator)
    {
    }

    void play(const std::string& track_title)
    {
        // creation of the object
        std::unique_ptr<MusicService> music_service = music_service_creator_->create_music_service();

        // usage of the object
        std::optional<Track> track = music_service->get_track(track_title);

        if (track)
        {
            std::cout << "Playing track: ";
            for (const auto& note : *track)
                std::cout << note << ".";
            std::cout << "|\n";
        }
        else
        {
            std::cout << "Track not found!\n";
        }
    }
};

// parametrized factory
using MusicServiceFactory = std::unordered_map<std::string, std::shared_ptr<MusicServiceCreator>>;

int main()
{
    MusicServiceFactory music_service_factory;
    music_service_factory.emplace("Tidal", std::make_shared<TidalServiceCreator>("tidal_user", "KJH8324d&df"));
    music_service_factory.emplace("Spotify", std::make_shared<SpotifyServiceCreator>("spotify_user", "rjdaslf276%2", 45));
    music_service_factory.emplace("Filesystem", std::make_shared<FsMusicServiceCreator>());

    std::string id_from_config = "Tidal";
    MusicApp app(music_service_factory.at(id_from_config));
    app.play("Would?");
}