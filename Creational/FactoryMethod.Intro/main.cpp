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

        void play(const std::string &track_title)
        {
            // creation of product
            SpotifyService music_service("spotify_user", "rjdaslf276%2", 45);

            std::optional<Track> track = music_service.get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto &note : *track)
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

namespace Canonical
{
    class MusicApp
    {
        std::shared_ptr<MusicServiceCreator> music_service_creator_;

    public:
        MusicApp(std::shared_ptr<MusicServiceCreator> music_service_creator)
            : music_service_creator_(music_service_creator)
        {
        }

        void play(const std::string &track_title)
        {
            // creation of the object
            std::unique_ptr<MusicService> music_service = music_service_creator_->create_music_service(); // delegation of the creation to the factory method of the creator class - decoupling the client from the concrete product classes

            // usage of the object
            std::optional<Track> track = music_service->get_track(track_title);

            if (track)
            {
                std::cout << "Playing track: ";
                for (const auto &note : *track)
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

void canonical_factory_method()
{
    using namespace Canonical;

    auto tidal_creator = std::make_shared<TidalServiceCreator>("tidal_user", "sdfj2%$#");
    auto spotify_creator = std::make_shared<SpotifyServiceCreator>("spotify_user", "rjdaslf276%2", 45);
    auto apple_creator = std::make_shared<AppleMusicServiceCreator>("apple_user", "apple_secret", 30);

    std::string id_from_config = "Tidal";
    Canonical::MusicApp app(apple_creator);
    app.play("Would?");
}

int main()
{
    std::cout << "Factory Method - Introduction\n";

    canonical_factory_method();

    return 0;
}