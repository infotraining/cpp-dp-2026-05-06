#ifndef CHAIN_HPP_
#define CHAIN_HPP_

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

using Temperature = double;

class DeviceHandler
{
    std::function<bool(Temperature)> can_handle_;
    std::function<void(Temperature)> handler_;

    std::shared_ptr<DeviceHandler> next_event_handler_;

public:
    template <typename TCanHandle, typename TEventHandler>
    DeviceHandler(TCanHandle&& can_handle, TEventHandler&& handler)
        : can_handle_{std::forward<TCanHandle>(can_handle)}
        , handler_{std::forward<TEventHandler>(handler)}
    { }

    void set_next_handler(std::shared_ptr<DeviceHandler> next_handler)
    {
        next_event_handler_ = next_handler;
    }

    void on_temperature_event(Temperature temperature)
    {
        if (can_handle_(temperature))
            handler_(temperature);

        if (next_event_handler_)
        {
            next_event_handler_->on_temperature_event(temperature);
        }
    }

    ~DeviceHandler() = default;
};

class Device
{
    std::string id_;
    std::shared_ptr<DeviceHandler> handler_;

public:
    Device(std::string id)
        : id_{id}
    {
    }

    template <typename TCanHandle, typename TDeviceHandler>
    void add_handler(TCanHandle&& can_handle, TDeviceHandler&& handler)
    {
        auto new_handler = std::make_shared<DeviceHandler>(std::forward<TCanHandle>(can_handle), std::forward<TDeviceHandler>(handler));
        new_handler->set_next_handler(handler_);
        handler_ = new_handler;
    }

    void on_temperature_change(Temperature temperature)
    {
        if (handler_)
            handler_->on_temperature_event(temperature);
    }
};

#endif /*CHAIN_HPP_*/
