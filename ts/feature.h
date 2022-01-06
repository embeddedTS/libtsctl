#ifndef __FEATURE_H
#define __FEATURE_H
#include <stdlib.h> // malloc/free

enum {
  FeatureErrorDLLNotFound=-1,
  FeatureErrorInitNotFound=-2,
  FeatureErrorFiniNotFound=-3,
  FeatureErrorInitError=-4,
  FeatureErrorAPINotFound1=-55,
  FeatureErrorAPINotFoundLimit=-99,
  FeatureErrorFileOpenBase=-100,
  ConfigErrorDependencyMissing=-50,
  ConfigErrorDependencyMissing2=-51,
  ConfigErrorLockStartMissing=-49,
  ConfigErrorLockCountMissing=-48,
  ConfigErrorMemBaseMissing=-47,
  ConfigErrorOffsetMissing=-46,
  ConfigErrorLengthMissing=-45,
  ConfigErrorWidthMissing=-44,
  ConfigErrorCountMissing=-43,
  ConfigErrorIRQMissing=-42,
  FPGAErrorShmgetBase=-1000,
  FPGAErrorShmdtBase=-2000,
  BusCacheErrorWidthInvalid=-40

};

#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
