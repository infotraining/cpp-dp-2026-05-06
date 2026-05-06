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

namespace ModernCpp
{
    class MusicApp
    {
        MusicServiceCreator music_service_factory_;

    public:
        MusicApp(MusicServiceCreator music_service_factory)
            : music_service_factory_(music_service_factory)
        {
        }

        void play(const std::string &track_title)
        {
            // creation of the object
            std::unique_ptr<MusicService> music_service = music_service_factory_();  

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

void modern_factory_method()
{
    using namespace ModernCpp;

    SpotifyServiceCreator spotify_creator("spotify_user", "rjdaslf276%2", 45);

    auto apple_creator = []() {
        return std::make_unique<AppleMusicService>("apple_user", "apple_secret", 30);
    };

    MusicApp app(apple_creator);
    app.play("Would?");
}

std::string parse_config_for_music_service()
{
    // In a real application, this would read from a config file or environment variable
    return "Apple"; // or "Tidal", "Apple", etc.
}

namespace ModernCpp
{
    class MusicServiceFactory
    {
        std::unordered_map<std::string, MusicServiceCreator> creators_;
    public:
        MusicServiceFactory() = default;

        void register_creator(const std::string& service_name, MusicServiceCreator creator)
        {
            creators_[service_name] = std::move(creator);
        }

        MusicServiceCreator create_music_service(const std::string& service_name)
        {
            auto it = creators_.find(service_name);
            if (it != creators_.end())
            {
                return it->second; // call the creator function to create the music service
            }
            throw std::runtime_error("Unknown music service: " + service_name);
        }
    };
}

int main()
{
    std::cout << "Factory Method - Introduction\n";

    // canonical_factory_method();
    modern_factory_method();

    ModernCpp::MusicServiceFactory music_service_factory;

    music_service_factory.register_creator("Spotify", ModernCpp::SpotifyServiceCreator("spotify_user", "rjdaslf276%2", 45));
    music_service_factory.register_creator("Apple", []() {
        return std::make_unique<AppleMusicService>("apple_user", "apple_secret", 30);
    });

    const std::string service_name = parse_config_for_music_service();
    ModernCpp::MusicApp music_app(music_service_factory.create_music_service(service_name));
    music_app.play("Would?");

    return 0;
}