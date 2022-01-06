#ifndef __NetMode_H
#define __NetMode_H
#include "NetTsctl.h"
#include "Mode.h"

typedef struct NetMode NetMode;

struct NetMode {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  void FUNC(JSON)(void *me);
  void FUNC(Assign)(void *me);
  void FUNC(NoAssign)(void *me);
  void FUNC(Hex)(void *me);
  void FUNC(Dec)(void *me);
  void FUNC(Oct)(void *me);
  void FUNC(AStr)(void *me);
  void FUNC(AHex)(void *me);
  void FUNC(ADec)(void *me);
  void FUNC(AOct)(void *me);
  void FUNC(ABinOct)(void *me);
  void FUNC(ABinHex)(void *me);
  void FUNC(ABinUni)(void *me);
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetModeInit(tsctl *,int instance);
void *NetModeFini(NetMode *);
void NetModeJSON(NetMode *ob);
void NetModeAssign(NetMode *ob);
void NetModeNoAssign(NetMode *ob);
void NetModeHex(NetMode *ob);
void NetModeDec(NetMode *ob);
void NetModeOct(NetMode *ob);
void NetModeAStr(NetMode *ob);
void NetModeAHex(NetMode *ob);
void NetModeADec(NetMode *ob);
void NetModeAOct(NetMode *ob);
void NetModeABinOct(NetMode *ob);
void NetModeABinHex(NetMode *ob);
void NetModeABinUni(NetMode *ob);
#endif
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
