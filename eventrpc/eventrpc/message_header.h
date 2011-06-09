/*
 * Copyright(C) lichuang
 */
#ifndef __EVENTRPC_MESSAGE_HEADER_H_
#define __EVENTRPC_MESSAGE_HEADER_H_
#include <string>
#include "eventrpc/base.h"
using std::string;
namespace eventrpc {
class Buffer;
enum ReadMessageState {
  READ_HEADER,
  READ_MESSAGE,
};
struct MessageHeader {
  uint32 opcode;
  uint32 length;
}__attribute__((packed));

struct MessageHandler {
  virtual ~MessageHandler() {}
  virtual bool HandlePacket(const MessageHeader &header,
                            Buffer* buffer) = 0;
 private:
  MessageHandler() {}
};
};
#endif  // __EVENTRPC_MESSAGE_HEADER_H_
