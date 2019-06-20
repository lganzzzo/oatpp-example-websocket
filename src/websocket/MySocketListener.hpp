//
// Created by Leonid  on 2019-03-13.
//

#ifndef MY_PROJECT_MYSOCKETLISTENER_HPP
#define MY_PROJECT_MYSOCKETLISTENER_HPP

#include "oatpp-websocket/ConnectionHandler.hpp"
#include "oatpp-websocket/WebSocket.hpp"

#include "oatpp/core/data/stream/ChunkedBuffer.hpp"

class MySocketListener : public oatpp::websocket::WebSocket::Listener {
private:
  static constexpr const char* const TAG = "MySocketListener";
private:
  oatpp::data::stream::ChunkedBuffer m_messageBuffer;
public:

  void onPing(const WebSocket& socket, const oatpp::String& message) override {
    OATPP_LOGD(TAG, "Ping frame received. Sending Pong back.");
    socket.sendPong("");
  }

  void onPong(const WebSocket& socket, const oatpp::String& message) override {
    OATPP_LOGD(TAG, "Pong frame received. Do nothing.");
    // DO NOTHING
  }

  void onClose(const WebSocket& socket, v_word16 code, const oatpp::String& message) override {
    OATPP_LOGD(TAG, "Close frame received. Code=%hd, Message='%s'", code, message->c_str());
  }

  /**
   * Called when "text" or "binary" frame received.
   * When all data of message is read, readMessage is called again with size == 0 to
   * indicate end of the message
   */
  void readMessage(const WebSocket& socket, v_word8 opcode, p_char8 data, oatpp::data::v_io_size size) override {
    if(size == 0) {
      auto wholeMessage = m_messageBuffer.toString();
      OATPP_LOGD(TAG, "Message='%s'", wholeMessage->c_str());
      socket.sendOneFrameText("Hello from oatpp! Your message was: " + wholeMessage);
      m_messageBuffer.clear();
    } else if(size > 0) {
      m_messageBuffer.write(data, size);
    }
  };

};

class MySocketInstanceListener : public oatpp::websocket::ConnectionHandler::SocketInstanceListener {
private:
  static constexpr const char* const TAG = "MySocketInstanceListener";
public:

  /**
   *  Called when socket is created
   */
  void onAfterCreate(const oatpp::websocket::WebSocket& socket, const std::shared_ptr<const ParameterMap>& params) override {
    OATPP_LOGD(TAG, "New incomming connection %d", &socket);
    
    // set listener
    socket.setListener(std::make_shared<MySocketListener>());
  }

  /**
   *  Called before socket instance is destroyed.
   */
  void onBeforeDestroy(const oatpp::websocket::WebSocket& socket) override {
    OATPP_LOGD(TAG, "Closing connection %d", &socket);
  }

};


#endif //MY_PROJECT_MYSOCKETLISTENER_HPP
