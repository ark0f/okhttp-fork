//
// Created by Good_Pudge.
//

#ifndef OKHTTPFORK_WEBSOCKET_HPP
#define OKHTTPFORK_WEBSOCKET_HPP

#include <string>
#include "Request.hpp"
#include "Response.hpp"
#include "Exception.hpp"

namespace ohf {
    class WebSocket {
    public:
        class Listener {
        public:
            virtual void onClosed(const WebSocket &webSocket, int code, const std::string &reason) = 0;
            virtual void onClosing(const WebSocket &webSocket, int code, const std::string &reason) = 0;
            virtual void onFailure(const WebSocket &webSocket, const Exception &e, const Response &response) = 0;
            virtual void onMessage(const WebSocket &webSocket, const std::vector<char> &bytes) = 0;
            virtual void onMessage(const WebSocket &webSocket, const std::string &text) = 0;
            virtual void onOpen(const WebSocket &webSocket, const Response &response) = 0;
        };

        class Factory {
        public:
            virtual WebSocket newWebSocket(const Request &request, const Listener &listener) = 0;
        };

        virtual void cancel() = 0;
        virtual bool close(int code, const std::string &reason) = 0;
        virtual long queueSize() = 0;
        virtual Request request() = 0;
        virtual bool send(const std::vector<char> &bytes) = 0;
        virtual bool send(const std::string &text) = 0;
    };
}

#endif //OKHTTPFORK_WEBSOCKET_HPP
