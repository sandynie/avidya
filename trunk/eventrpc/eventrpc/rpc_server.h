/*
 * Copyright(C) lichuang
 */
#ifndef __EVENTRPC_RPC_SERVER_H__
#define __EVENTRPC_RPC_SERVER_H__

#include <string>
#include "dispatcher.h"
#include "rpc_method_manager.h"
#include "rpc_connection_manager.h"

using std::string;

namespace eventrpc {
class RpcServer {
 public:
  RpcServer();

  ~RpcServer();

  void Start();

  void Stop();

  void set_host_and_port(const string &host, uint32 port) {
    host_ = host;
    port_ = port;
  }

  RpcMethodManager *rpc_method_manager() {
    return &rpc_method_manager_;
  }

  void set_dispatcher(Dispatcher *dispatcher) {
    dispatcher_ = dispatcher;
  }

  Dispatcher* dispatcher() {
    return dispatcher_;
  }

 private:
  int HandleAccept();

 private:
  string host_;
  uint32 port_;
  int listen_fd_;
  struct RpcServerEvent : public Event {
   public:
    RpcServerEvent(int fd, uint32 event_flags, RpcServer *server)
      : Event(fd, event_flags),
        server_(server) {
    }

    virtual ~RpcServerEvent() {
    }

    int HandleRead() {
      return server_->HandleAccept();
    }

    int HandleWrite() {
      return -1;
    }

   public:
    RpcServer *server_;
  };
  RpcServerEvent *event_;
  RpcMethodManager rpc_method_manager_;
  RpcConnectionManager rpc_connection_manager_;
  Dispatcher *dispatcher_;
};
};
#endif  //  __EVENTRPC_RPC_SERVER_H__
