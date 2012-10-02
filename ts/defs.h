void Output1000000(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	int n = 0;
	if (val == 0) { hprintf(oi->tsctl_o,"\n"); return; }
	if (val & 0x08) {
		hprintf(oi->tsctl_o,"%sERROR_WARNING",n++?"+":"");
	}
	if (val & 0x01) {
		hprintf(oi->tsctl_o,"%sBUS_ERROR",n++?"+":"");
	}
	if (val & 0x04) {
		hprintf(oi->tsctl_o,"%sDATA_OVERRUN",n++?"+":"");
	}
	if (val & 0x02) {
		hprintf(oi->tsctl_o,"%sERROR_PASSIVE",n++?"+":"");
	}
	if (val & 0x10) {
		hprintf(oi->tsctl_o,"%sRTR",n++?"+":"");
	}
	if (val & 0x20) {
		hprintf(oi->tsctl_o,"%sEXT",n++?"+":"");
	}
	hprintf(oi->tsctl_o,"\n");
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000001(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	int n = 0;
	if (val == 0) { hprintf(oi->tsctl_o,"\n"); return; }
	if (val & 0x01) {
		hprintf(oi->tsctl_o,"%sAIO_ADC",n++?"+":"");
	}
	if (val & 0x02) {
		hprintf(oi->tsctl_o,"%sAIO_DAC",n++?"+":"");
	}
	hprintf(oi->tsctl_o,"\n");
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000002(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	switch(val) {
		case 3: hprintf(oi->tsctl_o,"EDIO_EDGECOUNT"); break;
		case 1: hprintf(oi->tsctl_o,"EDIO_PWM"); break;
		case 4: hprintf(oi->tsctl_o,"EDIO_GLITCHED"); break;
		case 2: hprintf(oi->tsctl_o,"EDIO_QUADRATURE"); break;
		default: hprintf(oi->tsctl_o,"%d\n",val);
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000003(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	switch(val) {
		case 0: hprintf(oi->tsctl_o,"LOW"); break;
		case -1: hprintf(oi->tsctl_o,"INPUT"); break;
		case 1: hprintf(oi->tsctl_o,"HIGH"); break;
		case -2: hprintf(oi->tsctl_o,"INPUT_HIGH"); break;
		case -3: hprintf(oi->tsctl_o,"INPUT_LOW"); break;
		default: hprintf(oi->tsctl_o,"%d\n",val);
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000004(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	switch(val) {
		case 0: hprintf(oi->tsctl_o,"DIO_NOT_PRESENT"); break;
		case 1: hprintf(oi->tsctl_o,"DIO_INPUT_ONLY"); break;
		case 6: hprintf(oi->tsctl_o,"DIO_OUTPUT_ONLY"); break;
		case 4: hprintf(oi->tsctl_o,"DIO_CAN_DRIVE_LOW"); break;
		case 2: hprintf(oi->tsctl_o,"DIO_CAN_DRIVE_HIGH"); break;
		case 7: hprintf(oi->tsctl_o,"DIO_NORMAL"); break;
		default: hprintf(oi->tsctl_o,"%d\n",val);
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000005(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	switch(val) {
		case 0: hprintf(oi->tsctl_o,"MODE_DIO"); break;
		case 3: hprintf(oi->tsctl_o,"MODE_ADC"); break;
		case -1: hprintf(oi->tsctl_o,"MODE_UNKNOWN"); break;
		case 8: hprintf(oi->tsctl_o,"MODE_PWM"); break;
		case 1: hprintf(oi->tsctl_o,"MODE_CAN"); break;
		case 6: hprintf(oi->tsctl_o,"MODE_TS"); break;
		case 4: hprintf(oi->tsctl_o,"MODE_TWI"); break;
		case 5: hprintf(oi->tsctl_o,"MODE_UART"); break;
		case 2: hprintf(oi->tsctl_o,"MODE_SPI"); break;
		case 7: hprintf(oi->tsctl_o,"MODE_BUS"); break;
		default: hprintf(oi->tsctl_o,"%d\n",val);
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000006(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	int n = 0;
	if (val == 0) { hprintf(oi->tsctl_o,"\n"); return; }
	if (val & 0x400000) {
		hprintf(oi->tsctl_o,"%sLOG_DIOCTL",n++?"+":"");
	}
	if (val & 0x8000000) {
		hprintf(oi->tsctl_o,"%sLOG_RETURN",n++?"+":"");
	}
	if (val & 0x4000000) {
		hprintf(oi->tsctl_o,"%sLOG_DEPTH",n++?"+":"");
	}
	if (val & 0x800000) {
		hprintf(oi->tsctl_o,"%sLOG_TIMESTAMP",n++?"+":"");
	}
	if (val & 0x40000000) {
		hprintf(oi->tsctl_o,"%sLOG_FUNCTION",n++?"+":"");
	}
	if (val & 0x08) {
		hprintf(oi->tsctl_o,"%sLOG_PIN",n++?"+":"");
	}
	if (val & 0x01) {
		hprintf(oi->tsctl_o,"%sLOG_SYSTEM",n++?"+":"");
	}
	if (val & 0x80) {
		hprintf(oi->tsctl_o,"%sLOG_CAN",n++?"+":"");
	}
	if (val & 0x80000000) {
		hprintf(oi->tsctl_o,"%sLOG_FILELINE",n++?"+":"");
	}
	if (val & 0x04) {
		hprintf(oi->tsctl_o,"%sLOG_TIME",n++?"+":"");
	}
	if (val & 0x100) {
		hprintf(oi->tsctl_o,"%sLOG_SPI",n++?"+":"");
	}
	if (val & 0x20000000) {
		hprintf(oi->tsctl_o,"%sLOG_THREADID",n++?"+":"");
	}
	if (val & 0x02) {
		hprintf(oi->tsctl_o,"%sLOG_BUS",n++?"+":"");
	}
	if (val & 0x10000000) {
		hprintf(oi->tsctl_o,"%sLOG_ENTER",n++?"+":"");
	}
	if (val & 0x100000) {
		hprintf(oi->tsctl_o,"%sLOG_ASSERT",n++?"+":"");
	}
	if (val & 0x40) {
		hprintf(oi->tsctl_o,"%sLOG_TWI",n++?"+":"");
	}
	if (val & 0x10) {
		hprintf(oi->tsctl_o,"%sLOG_DIORAW",n++?"+":"");
	}
	if (val & 0x200000) {
		hprintf(oi->tsctl_o,"%sLOG_THREAD",n++?"+":"");
	}
	if (val & 0x20) {
		hprintf(oi->tsctl_o,"%sLOG_DIO",n++?"+":"");
	}
	hprintf(oi->tsctl_o,"\n");
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000007(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	switch(val) {
		case 0: hprintf(oi->tsctl_o,"ClassSystem"); break;
		case 10: hprintf(oi->tsctl_o,"ClassEDIO"); break;
		case 3: hprintf(oi->tsctl_o,"ClassPin"); break;
		case 8: hprintf(oi->tsctl_o,"ClassSPI"); break;
		case 1: hprintf(oi->tsctl_o,"ClassBus"); break;
		case 11: hprintf(oi->tsctl_o,"ClassAIO"); break;
		case 6: hprintf(oi->tsctl_o,"ClassTWI"); break;
		case 4: hprintf(oi->tsctl_o,"ClassDIORaw"); break;
		case 5: hprintf(oi->tsctl_o,"ClassDIO"); break;
		case 2: hprintf(oi->tsctl_o,"ClassTime"); break;
		case 7: hprintf(oi->tsctl_o,"ClassCAN"); break;
		default: hprintf(oi->tsctl_o,"%d\n",val);
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000008(OutInfo *oi,char *name,int val) {
	if (oi->fAssign) {
		if (oi->ht) {
			if (oi->fAssign==2) {
				hprintf(oi->tsctl_o,"\"%s_%d\":",name,htCount(oi->ht,name));
			} else {
				hprintf(oi->tsctl_o,"%s_%d=",name,htCount(oi->ht,name));
			}
		} else {
			hprintf(oi->tsctl_o,"%s=",name);
		}
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\"");
	switch(val) {
		case 3: hprintf(oi->tsctl_o,"HB_FREE_RUNNING"); break;
		case 1: hprintf(oi->tsctl_o,"HB_LEFT"); break;
		case 4: hprintf(oi->tsctl_o,"HB_BRAKING"); break;
		case 2: hprintf(oi->tsctl_o,"HB_RIGHT"); break;
		default: hprintf(oi->tsctl_o,"%d\n",val);
	}
	if (oi->fAssign==2) hprintf(oi->tsctl_o,"\",\n");
	  else hprintf(oi->tsctl_o,"\n");
}
void Output1000009(OutInfo *oi,char *name,LockHolderInfo* arg) {
	int i;
	for (i=0;i<ArrayLength(arg);i++) {
		Output_32(oi,"pid",(arg+i)->pid);
		Output_32(oi,"count",(arg+i)->count);
	}
}

void Output1000010(OutInfo *oi,char *name,ConnectionWaitInfo* arg) {
	int i;
	for (i=0;i<ArrayLength(arg);i++) {
		Output_32(oi,"pid",(arg+i)->pid);
		Output_32(oi,"wait",(arg+i)->wait);
	}
}

void Output1000011(OutInfo *oi,char *name,BuildInfo* arg) {
	int i;
	for (i=0;i<ArrayLength(arg);i++) {
		Output32(oi,"buildTime",(arg+i)->buildTime);
		Output32(oi,"uptime",(arg+i)->uptime);
		Output_1008(oi,"hostname",(arg+i)->hostname);
		Output_1008(oi,"arch",(arg+i)->arch);
	}
}

void Output1000012(OutInfo *oi,char *name,VoltageRange* arg) {
	int i;
	for (i=0;i<ArrayLength(arg);i++) {
		Output900(oi,"low.start",(arg+i)->low.start);
		Output900(oi,"low.step",(arg+i)->low.step);
		Output32(oi,"low.count",(arg+i)->low.count);
		Output900(oi,"high.start",(arg+i)->high.start);
		Output900(oi,"high.step",(arg+i)->high.step);
		Output32(oi,"high.count",(arg+i)->high.count);
	}
}

void Output1000013(OutInfo *oi,char *name,PeriodRange* arg) {
	int i;
	for (i=0;i<ArrayLength(arg);i++) {
		Output32(oi,"start",(arg+i)->start);
		Output32(oi,"step",(arg+i)->step);
		Output32(oi,"count",(arg+i)->count);
	}
}


System** SystemArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t Systemmutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int ClassCount(void *me);
// ClassCount
// ->
// <int>
ArrayAuto(int,reqtypesSystem1,ARR());
ArrayAuto(int,replytypesSystem1,ARR(-32));
void SystemCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = SystemArr[inst]->ClassCount(SystemArr[inst]);
	Output_32(oi,"ClassCount",ret);
}
prototype protSystem1 = {
	NetSystem_ClassCount,
	ArrayL(reqtypesSystem1),ArrayL(replytypesSystem1),
	SystemCommand1
};

// int InstanceCount(void *me,int);
// InstanceCount <int>
// ->
// <int>
ArrayAuto(int,reqtypesSystem2,ARR(-32));
ArrayAuto(int,replytypesSystem2,ARR(-32));
void SystemCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = SystemArr[inst]->InstanceCount(SystemArr[inst],arg0);
	Output_32(oi,"InstanceCount",ret);
}
prototype protSystem2 = {
	NetSystem_InstanceCount,
	ArrayL(reqtypesSystem2),ArrayL(replytypesSystem2),
	SystemCommand2
};

// int APICount(void *me,int);
// APICount <int>
// ->
// <int>
ArrayAuto(int,reqtypesSystem3,ARR(-32));
ArrayAuto(int,replytypesSystem3,ARR(-32));
void SystemCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = SystemArr[inst]->APICount(SystemArr[inst],arg0);
	Output_32(oi,"APICount",ret);
}
prototype protSystem3 = {
	NetSystem_APICount,
	ArrayL(reqtypesSystem3),ArrayL(replytypesSystem3),
	SystemCommand3
};

// int LockCount(void *me);
// LockCount
// ->
// <int>
ArrayAuto(int,reqtypesSystem4,ARR());
ArrayAuto(int,replytypesSystem4,ARR(-32));
void SystemCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = SystemArr[inst]->LockCount(SystemArr[inst]);
	Output_32(oi,"LockCount",ret);
}
prototype protSystem4 = {
	NetSystem_LockCount,
	ArrayL(reqtypesSystem4),ArrayL(replytypesSystem4),
	SystemCommand4
};

// LockHolderInfo* LockHolderInfo(void *me);
// LockHolderInfo
// ->
// <LockHolderInfo*>
ArrayAuto(int,reqtypesSystem5,ARR());
ArrayAuto(int,replytypesSystem5,ARR(1000009));
void SystemCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	LockHolderInfo* ret = SystemArr[inst]->LockHolderInfo(SystemArr[inst]);
	Output1000009(oi,"LockHolderInfo",ret);
	ArrayFree(ret);
}
prototype protSystem5 = {
	NetSystem_LockHolderInfo,
	ArrayL(reqtypesSystem5),ArrayL(replytypesSystem5),
	SystemCommand5
};

// ConnectionWaitInfo* ConnWaitInfo(void *me);
// ConnWaitInfo
// ->
// <ConnectionWaitInfo*>
ArrayAuto(int,reqtypesSystem6,ARR());
ArrayAuto(int,replytypesSystem6,ARR(1000010));
void SystemCommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	ConnectionWaitInfo* ret = SystemArr[inst]->ConnWaitInfo(SystemArr[inst]);
	Output1000010(oi,"ConnWaitInfo",ret);
	ArrayFree(ret);
}
prototype protSystem6 = {
	NetSystem_ConnWaitInfo,
	ArrayL(reqtypesSystem6),ArrayL(replytypesSystem6),
	SystemCommand6
};

// int CANBusGet(void *me,int);
// CANBusGet <int>
// ->
// <int>
ArrayAuto(int,reqtypesSystem7,ARR(-32));
ArrayAuto(int,replytypesSystem7,ARR(-32));
void SystemCommand7(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = SystemArr[inst]->CANBusGet(SystemArr[inst],arg0);
	Output_32(oi,"CANBusGet",ret);
}
prototype protSystem7 = {
	NetSystem_CANBusGet,
	ArrayL(reqtypesSystem7),ArrayL(replytypesSystem7),
	SystemCommand7
};

// void BuildInfo(void *me,BuildInfo[1]);
// BuildInfo
// ->
// <BuildInfo*>
ArrayAuto(int,reqtypesSystem8,ARR());
ArrayAuto(int,replytypesSystem8,ARR(1000011));
void SystemCommand8(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	BuildInfo *arg0 = ArrayAlloc(1,sizeof(BuildInfo));
	SystemArr[inst]->BuildInfo(SystemArr[inst],arg0);
	Output1000011(oi,"BuildInfo",arg0);
	ArrayFree(arg0);
}
prototype protSystem8 = {
	NetSystem_BuildInfo,
	ArrayL(reqtypesSystem8),ArrayL(replytypesSystem8),
	SystemCommand8
};

// int ModelId(void *me);
// ModelId
// ->
// <int>
ArrayAuto(int,reqtypesSystem9,ARR());
ArrayAuto(int,replytypesSystem9,ARR(-32));
void SystemCommand9(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = SystemArr[inst]->ModelId(SystemArr[inst]);
	Output_32(oi,"ModelId",ret);
}
prototype protSystem9 = {
	NetSystem_ModelId,
	ArrayL(reqtypesSystem9),ArrayL(replytypesSystem9),
	SystemCommand9
};

// int BaseBoardId(void *me);
// BaseBoardId
// ->
// <int>
ArrayAuto(int,reqtypesSystem10,ARR());
ArrayAuto(int,replytypesSystem10,ARR(-32));
void SystemCommand10(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = SystemArr[inst]->BaseBoardId(SystemArr[inst]);
	Output_32(oi,"BaseBoardId",ret);
}
prototype protSystem10 = {
	NetSystem_BaseBoardId,
	ArrayL(reqtypesSystem10),ArrayL(replytypesSystem10),
	SystemCommand10
};

// int MapLength(void *me);
// MapLength
// ->
// <int>
ArrayAuto(int,reqtypesSystem11,ARR());
ArrayAuto(int,replytypesSystem11,ARR(-32));
void SystemCommand11(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = SystemArr[inst]->MapLength(SystemArr[inst]);
	Output_32(oi,"MapLength",ret);
}
prototype protSystem11 = {
	NetSystem_MapLength,
	ArrayL(reqtypesSystem11),ArrayL(replytypesSystem11),
	SystemCommand11
};

// char* MapGet(void *me,int,int[1]);
// MapGet <int>
// ->
// <char*> <int*>
ArrayAuto(int,reqtypesSystem12,ARR(-32));
ArrayAuto(int,replytypesSystem12,ARR(-1008,-1032));
void SystemCommand12(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int *arg1 = ArrayAlloc(1,sizeof(int));
	char* ret = SystemArr[inst]->MapGet(SystemArr[inst],arg0,arg1);
	Output_1008(oi,"MapGet",ret);
	Output_1032(oi,"MapGet",arg1);
	ArrayFree(arg1);
	ArrayFree(ret);
}
prototype protSystem12 = {
	NetSystem_MapGet,
	ArrayL(reqtypesSystem12),ArrayL(replytypesSystem12),
	SystemCommand12
};

// int MapLookup(void *me,const char*);
// MapLookup <char*>
// ->
// <int>
ArrayAuto(int,reqtypesSystem13,ARR(-1008));
ArrayAuto(int,replytypesSystem13,ARR(-32));
void SystemCommand13(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	const char* arg0 = Input_1008(argv[0]);
	int ret = SystemArr[inst]->MapLookup(SystemArr[inst],arg0);
	Output_32(oi,"MapLookup",ret);
	ArrayFree(arg0);
}
prototype protSystem13 = {
	NetSystem_MapLookup,
	ArrayL(reqtypesSystem13),ArrayL(replytypesSystem13),
	SystemCommand13
};

// char* MapLookupPartial(void *me,const char*,int);
// MapLookupPartial <char*> <int>
// ->
// <char*>
ArrayAuto(int,reqtypesSystem14,ARR(-1008,-32));
ArrayAuto(int,replytypesSystem14,ARR(-1008));
void SystemCommand14(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	const char* arg0 = Input_1008(argv[0]);
	int arg1 = Input_32(argv[1]);
	char* ret = SystemArr[inst]->MapLookupPartial(SystemArr[inst],arg0,arg1);
	Output_1008(oi,"MapLookupPartial",ret);
	ArrayFree(arg0);
	ArrayFree(ret);
}
prototype protSystem14 = {
	NetSystem_MapLookupPartial,
	ArrayL(reqtypesSystem14),ArrayL(replytypesSystem14),
	SystemCommand14
};

// int MapAdd(void *me,const char*,int);
// MapAdd <char*> <int>
// ->
// <int>
ArrayAuto(int,reqtypesSystem15,ARR(-1008,-32));
ArrayAuto(int,replytypesSystem15,ARR(-32));
void SystemCommand15(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	const char* arg0 = Input_1008(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = SystemArr[inst]->MapAdd(SystemArr[inst],arg0,arg1);
	Output_32(oi,"MapAdd",ret);
	ArrayFree(arg0);
}
prototype protSystem15 = {
	NetSystem_MapAdd,
	ArrayL(reqtypesSystem15),ArrayL(replytypesSystem15),
	SystemCommand15
};

// int MapDelete(void *me,const char*);
// MapDelete <char*>
// ->
// <int>
ArrayAuto(int,reqtypesSystem16,ARR(-1008));
ArrayAuto(int,replytypesSystem16,ARR(-32));
void SystemCommand16(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Systemmutex);
#endif
	if (!SystemArr) {
		SystemArr = ArrayAlloc(inst+1,sizeof(System *));
		for (i=0;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i]= SystemInit(inst);
	} else if (inst >= ArrayLength(SystemArr)) {
		i = ArrayLength(SystemArr);
		SystemArr = ArraySize(SystemArr,inst+1);
		for (;i<inst;i++) SystemArr[i] = 0;
		SystemArr[i] = SystemInit(inst);
	} else {
		if (!SystemArr[inst]) SystemArr[inst] = SystemInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Systemmutex);
#endif
	if (!SystemArr[inst]) { Output_32(oi,"Error",-2); return; }
	const char* arg0 = Input_1008(argv[0]);
	int ret = SystemArr[inst]->MapDelete(SystemArr[inst],arg0);
	Output_32(oi,"MapDelete",ret);
	ArrayFree(arg0);
}
prototype protSystem16 = {
	NetSystem_MapDelete,
	ArrayL(reqtypesSystem16),ArrayL(replytypesSystem16),
	SystemCommand16
};


Bus** BusArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t Busmutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Lock(void *me,uint,int);
// Lock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesBus1,ARR(32,-32));
ArrayAuto(int,replytypesBus1,ARR(-32));
void BusCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = BusArr[inst]->Lock(BusArr[inst],arg0,arg1);
	Output_32(oi,"Lock",ret);
}
prototype protBus1 = {
	NetBus_Lock,
	ArrayL(reqtypesBus1),ArrayL(replytypesBus1),
	BusCommand1
};

// int Unlock(void *me,uint,int);
// Unlock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesBus2,ARR(32,-32));
ArrayAuto(int,replytypesBus2,ARR(-32));
void BusCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = BusArr[inst]->Unlock(BusArr[inst],arg0,arg1);
	Output_32(oi,"Unlock",ret);
}
prototype protBus2 = {
	NetBus_Unlock,
	ArrayL(reqtypesBus2),ArrayL(replytypesBus2),
	BusCommand2
};

// int Preempt(void *me);
// Preempt
// ->
// <int>
ArrayAuto(int,reqtypesBus3,ARR());
ArrayAuto(int,replytypesBus3,ARR(-32));
void BusCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = BusArr[inst]->Preempt(BusArr[inst]);
	Output_32(oi,"Preempt",ret);
}
prototype protBus3 = {
	NetBus_Preempt,
	ArrayL(reqtypesBus3),ArrayL(replytypesBus3),
	BusCommand3
};

// uchar Peek8(void *me,int);
// Peek8 <int>
// ->
// <uchar>
ArrayAuto(int,reqtypesBus4,ARR(-32));
ArrayAuto(int,replytypesBus4,ARR(8));
void BusCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uchar ret = BusArr[inst]->Peek8(BusArr[inst],arg0);
	Output8(oi,"Peek8",ret);
}
prototype protBus4 = {
	NetBus_Peek8,
	ArrayL(reqtypesBus4),ArrayL(replytypesBus4),
	BusCommand4
};

// void Poke8(void *me,int,uchar);
// Poke8 <int> <uchar>
// ->
//
ArrayAuto(int,reqtypesBus5,ARR(-32,8));
ArrayAuto(int,replytypesBus5,ARR());
void BusCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uchar arg1 = Input8(argv[1]);
	BusArr[inst]->Poke8(BusArr[inst],arg0,arg1);
}
prototype protBus5 = {
	NetBus_Poke8,
	ArrayL(reqtypesBus5),ArrayL(replytypesBus5),
	BusCommand5
};

// ushort Peek16(void *me,int);
// Peek16 <int>
// ->
// <ushort>
ArrayAuto(int,reqtypesBus6,ARR(-32));
ArrayAuto(int,replytypesBus6,ARR(16));
void BusCommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	ushort ret = BusArr[inst]->Peek16(BusArr[inst],arg0);
	Output16(oi,"Peek16",ret);
}
prototype protBus6 = {
	NetBus_Peek16,
	ArrayL(reqtypesBus6),ArrayL(replytypesBus6),
	BusCommand6
};

// void Poke16(void *me,int,ushort);
// Poke16 <int> <ushort>
// ->
//
ArrayAuto(int,reqtypesBus7,ARR(-32,16));
ArrayAuto(int,replytypesBus7,ARR());
void BusCommand7(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	ushort arg1 = Input16(argv[1]);
	BusArr[inst]->Poke16(BusArr[inst],arg0,arg1);
}
prototype protBus7 = {
	NetBus_Poke16,
	ArrayL(reqtypesBus7),ArrayL(replytypesBus7),
	BusCommand7
};

// uint Peek32(void *me,int);
// Peek32 <int>
// ->
// <uint>
ArrayAuto(int,reqtypesBus8,ARR(-32));
ArrayAuto(int,replytypesBus8,ARR(32));
void BusCommand8(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uint ret = BusArr[inst]->Peek32(BusArr[inst],arg0);
	Output32(oi,"Peek32",ret);
}
prototype protBus8 = {
	NetBus_Peek32,
	ArrayL(reqtypesBus8),ArrayL(replytypesBus8),
	BusCommand8
};

// void Poke32(void *me,int,uint);
// Poke32 <int> <uint>
// ->
//
ArrayAuto(int,reqtypesBus9,ARR(-32,32));
ArrayAuto(int,replytypesBus9,ARR());
void BusCommand9(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uint arg1 = Input32(argv[1]);
	BusArr[inst]->Poke32(BusArr[inst],arg0,arg1);
}
prototype protBus9 = {
	NetBus_Poke32,
	ArrayL(reqtypesBus9),ArrayL(replytypesBus9),
	BusCommand9
};

// int BitGet8(void *me,int,int);
// BitGet8 <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesBus10,ARR(-32,-32));
ArrayAuto(int,replytypesBus10,ARR(-32));
void BusCommand10(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = BusArr[inst]->BitGet8(BusArr[inst],arg0,arg1);
	Output_32(oi,"BitGet8",ret);
}
prototype protBus10 = {
	NetBus_BitGet8,
	ArrayL(reqtypesBus10),ArrayL(replytypesBus10),
	BusCommand10
};

// void BitAssign8(void *me,int,int,int);
// BitAssign8 <int> <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus11,ARR(-32,-32,-32));
ArrayAuto(int,replytypesBus11,ARR());
void BusCommand11(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	BusArr[inst]->BitAssign8(BusArr[inst],arg0,arg1,arg2);
}
prototype protBus11 = {
	NetBus_BitAssign8,
	ArrayL(reqtypesBus11),ArrayL(replytypesBus11),
	BusCommand11
};

// void BitSet8(void *me,int,int);
// BitSet8 <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus12,ARR(-32,-32));
ArrayAuto(int,replytypesBus12,ARR());
void BusCommand12(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	BusArr[inst]->BitSet8(BusArr[inst],arg0,arg1);
}
prototype protBus12 = {
	NetBus_BitSet8,
	ArrayL(reqtypesBus12),ArrayL(replytypesBus12),
	BusCommand12
};

// void BitClear8(void *me,int,int);
// BitClear8 <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus13,ARR(-32,-32));
ArrayAuto(int,replytypesBus13,ARR());
void BusCommand13(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	BusArr[inst]->BitClear8(BusArr[inst],arg0,arg1);
}
prototype protBus13 = {
	NetBus_BitClear8,
	ArrayL(reqtypesBus13),ArrayL(replytypesBus13),
	BusCommand13
};

// int BitGet16(void *me,int,int);
// BitGet16 <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesBus14,ARR(-32,-32));
ArrayAuto(int,replytypesBus14,ARR(-32));
void BusCommand14(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = BusArr[inst]->BitGet16(BusArr[inst],arg0,arg1);
	Output_32(oi,"BitGet16",ret);
}
prototype protBus14 = {
	NetBus_BitGet16,
	ArrayL(reqtypesBus14),ArrayL(replytypesBus14),
	BusCommand14
};

// void BitAssign16(void *me,int,int,int);
// BitAssign16 <int> <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus15,ARR(-32,-32,-32));
ArrayAuto(int,replytypesBus15,ARR());
void BusCommand15(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	BusArr[inst]->BitAssign16(BusArr[inst],arg0,arg1,arg2);
}
prototype protBus15 = {
	NetBus_BitAssign16,
	ArrayL(reqtypesBus15),ArrayL(replytypesBus15),
	BusCommand15
};

// void BitSet16(void *me,int,int);
// BitSet16 <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus16,ARR(-32,-32));
ArrayAuto(int,replytypesBus16,ARR());
void BusCommand16(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	BusArr[inst]->BitSet16(BusArr[inst],arg0,arg1);
}
prototype protBus16 = {
	NetBus_BitSet16,
	ArrayL(reqtypesBus16),ArrayL(replytypesBus16),
	BusCommand16
};

// void BitClear16(void *me,int,int);
// BitClear16 <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus17,ARR(-32,-32));
ArrayAuto(int,replytypesBus17,ARR());
void BusCommand17(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	BusArr[inst]->BitClear16(BusArr[inst],arg0,arg1);
}
prototype protBus17 = {
	NetBus_BitClear16,
	ArrayL(reqtypesBus17),ArrayL(replytypesBus17),
	BusCommand17
};

// int BitGet32(void *me,int,int);
// BitGet32 <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesBus18,ARR(-32,-32));
ArrayAuto(int,replytypesBus18,ARR(-32));
void BusCommand18(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = BusArr[inst]->BitGet32(BusArr[inst],arg0,arg1);
	Output_32(oi,"BitGet32",ret);
}
prototype protBus18 = {
	NetBus_BitGet32,
	ArrayL(reqtypesBus18),ArrayL(replytypesBus18),
	BusCommand18
};

// void BitAssign32(void *me,int,int,int);
// BitAssign32 <int> <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus19,ARR(-32,-32,-32));
ArrayAuto(int,replytypesBus19,ARR());
void BusCommand19(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	BusArr[inst]->BitAssign32(BusArr[inst],arg0,arg1,arg2);
}
prototype protBus19 = {
	NetBus_BitAssign32,
	ArrayL(reqtypesBus19),ArrayL(replytypesBus19),
	BusCommand19
};

// void BitSet32(void *me,int,int);
// BitSet32 <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus20,ARR(-32,-32));
ArrayAuto(int,replytypesBus20,ARR());
void BusCommand20(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	BusArr[inst]->BitSet32(BusArr[inst],arg0,arg1);
}
prototype protBus20 = {
	NetBus_BitSet32,
	ArrayL(reqtypesBus20),ArrayL(replytypesBus20),
	BusCommand20
};

// void BitClear32(void *me,int,int);
// BitClear32 <int> <int>
// ->
//
ArrayAuto(int,reqtypesBus21,ARR(-32,-32));
ArrayAuto(int,replytypesBus21,ARR());
void BusCommand21(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	BusArr[inst]->BitClear32(BusArr[inst],arg0,arg1);
}
prototype protBus21 = {
	NetBus_BitClear32,
	ArrayL(reqtypesBus21),ArrayL(replytypesBus21),
	BusCommand21
};

// void PeekStream(void *me,int,int,char*);
// PeekStream <int> <int>
// ->
// <char*>
ArrayAuto(int,reqtypesBus22,ARR(-32,-32));
ArrayAuto(int,replytypesBus22,ARR(-1008));
void BusCommand22(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	char* arg2 = ArrayAlloc(Input32(argv[2]),sizeof(char));
	BusArr[inst]->PeekStream(BusArr[inst],arg0,arg1,arg2);
	Output_1008(oi,"PeekStream",arg2);
	ArrayFree(arg2);
}
prototype protBus22 = {
	NetBus_PeekStream,
	ArrayL(reqtypesBus22),ArrayL(replytypesBus22),
	BusCommand22
};

// void PokeStream(void *me,int,int,const char*);
// PokeStream <int> <int> <char*>
// ->
//
ArrayAuto(int,reqtypesBus23,ARR(-32,-32,-1008));
ArrayAuto(int,replytypesBus23,ARR());
void BusCommand23(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	const char* arg2 = Input_1008(argv[2]);
	BusArr[inst]->PokeStream(BusArr[inst],arg0,arg1,arg2);
	ArrayFree(arg2);
}
prototype protBus23 = {
	NetBus_PokeStream,
	ArrayL(reqtypesBus23),ArrayL(replytypesBus23),
	BusCommand23
};

// void Refresh(void *me);
// Refresh
// ->
//
ArrayAuto(int,reqtypesBus24,ARR());
ArrayAuto(int,replytypesBus24,ARR());
void BusCommand24(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	BusArr[inst]->Refresh(BusArr[inst]);
}
prototype protBus24 = {
	NetBus_Refresh,
	ArrayL(reqtypesBus24),ArrayL(replytypesBus24),
	BusCommand24
};

// void Commit(void *me,int);
// Commit <int>
// ->
//
ArrayAuto(int,reqtypesBus25,ARR(-32));
ArrayAuto(int,replytypesBus25,ARR());
void BusCommand25(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	BusArr[inst]->Commit(BusArr[inst],arg0);
}
prototype protBus25 = {
	NetBus_Commit,
	ArrayL(reqtypesBus25),ArrayL(replytypesBus25),
	BusCommand25
};

// int BitToggle8(void *me,int,int);
// BitToggle8 <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesBus26,ARR(-32,-32));
ArrayAuto(int,replytypesBus26,ARR(-32));
void BusCommand26(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = BusArr[inst]->BitToggle8(BusArr[inst],arg0,arg1);
	Output_32(oi,"BitToggle8",ret);
}
prototype protBus26 = {
	NetBus_BitToggle8,
	ArrayL(reqtypesBus26),ArrayL(replytypesBus26),
	BusCommand26
};

// int BitToggle16(void *me,int,int);
// BitToggle16 <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesBus27,ARR(-32,-32));
ArrayAuto(int,replytypesBus27,ARR(-32));
void BusCommand27(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = BusArr[inst]->BitToggle16(BusArr[inst],arg0,arg1);
	Output_32(oi,"BitToggle16",ret);
}
prototype protBus27 = {
	NetBus_BitToggle16,
	ArrayL(reqtypesBus27),ArrayL(replytypesBus27),
	BusCommand27
};

// int BitToggle32(void *me,int,int);
// BitToggle32 <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesBus28,ARR(-32,-32));
ArrayAuto(int,replytypesBus28,ARR(-32));
void BusCommand28(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = BusArr[inst]->BitToggle32(BusArr[inst],arg0,arg1);
	Output_32(oi,"BitToggle32",ret);
}
prototype protBus28 = {
	NetBus_BitToggle32,
	ArrayL(reqtypesBus28),ArrayL(replytypesBus28),
	BusCommand28
};

// uchar Assign8X(void *me,int,int,int,int);
// Assign8X <int> <int> <int> <int>
// ->
// <uchar>
ArrayAuto(int,reqtypesBus29,ARR(-32,-32,-32,-32));
ArrayAuto(int,replytypesBus29,ARR(8));
void BusCommand29(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	int arg3 = Input_32(argv[3]);
	uchar ret = BusArr[inst]->Assign8X(BusArr[inst],arg0,arg1,arg2,arg3);
	Output8(oi,"Assign8X",ret);
}
prototype protBus29 = {
	NetBus_Assign8X,
	ArrayL(reqtypesBus29),ArrayL(replytypesBus29),
	BusCommand29
};

// short Assign16X(void *me,int,int,int,int);
// Assign16X <int> <int> <int> <int>
// ->
// <short>
ArrayAuto(int,reqtypesBus30,ARR(-32,-32,-32,-32));
ArrayAuto(int,replytypesBus30,ARR(-16));
void BusCommand30(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	int arg3 = Input_32(argv[3]);
	short ret = BusArr[inst]->Assign16X(BusArr[inst],arg0,arg1,arg2,arg3);
	Output_16(oi,"Assign16X",ret);
}
prototype protBus30 = {
	NetBus_Assign16X,
	ArrayL(reqtypesBus30),ArrayL(replytypesBus30),
	BusCommand30
};

// uint Assign32X(void *me,int,int,int,int);
// Assign32X <int> <int> <int> <int>
// ->
// <uint>
ArrayAuto(int,reqtypesBus31,ARR(-32,-32,-32,-32));
ArrayAuto(int,replytypesBus31,ARR(32));
void BusCommand31(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	int arg3 = Input_32(argv[3]);
	uint ret = BusArr[inst]->Assign32X(BusArr[inst],arg0,arg1,arg2,arg3);
	Output32(oi,"Assign32X",ret);
}
prototype protBus31 = {
	NetBus_Assign32X,
	ArrayL(reqtypesBus31),ArrayL(replytypesBus31),
	BusCommand31
};

// uchar BitsGet8(void *me,int,int,int);
// BitsGet8 <int> <int> <int>
// ->
// <uchar>
ArrayAuto(int,reqtypesBus32,ARR(-32,-32,-32));
ArrayAuto(int,replytypesBus32,ARR(8));
void BusCommand32(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	uchar ret = BusArr[inst]->BitsGet8(BusArr[inst],arg0,arg1,arg2);
	Output8(oi,"BitsGet8",ret);
}
prototype protBus32 = {
	NetBus_BitsGet8,
	ArrayL(reqtypesBus32),ArrayL(replytypesBus32),
	BusCommand32
};

// ushort BitsGet16(void *me,int,int,int);
// BitsGet16 <int> <int> <int>
// ->
// <ushort>
ArrayAuto(int,reqtypesBus33,ARR(-32,-32,-32));
ArrayAuto(int,replytypesBus33,ARR(16));
void BusCommand33(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	ushort ret = BusArr[inst]->BitsGet16(BusArr[inst],arg0,arg1,arg2);
	Output16(oi,"BitsGet16",ret);
}
prototype protBus33 = {
	NetBus_BitsGet16,
	ArrayL(reqtypesBus33),ArrayL(replytypesBus33),
	BusCommand33
};

// uint BitsGet32(void *me,int,int,int);
// BitsGet32 <int> <int> <int>
// ->
// <uint>
ArrayAuto(int,reqtypesBus34,ARR(-32,-32,-32));
ArrayAuto(int,replytypesBus34,ARR(32));
void BusCommand34(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Busmutex);
#endif
	if (!BusArr) {
		BusArr = ArrayAlloc(inst+1,sizeof(Bus *));
		for (i=0;i<inst;i++) BusArr[i] = 0;
		BusArr[i]= BusInit(inst);
	} else if (inst >= ArrayLength(BusArr)) {
		i = ArrayLength(BusArr);
		BusArr = ArraySize(BusArr,inst+1);
		for (;i<inst;i++) BusArr[i] = 0;
		BusArr[i] = BusInit(inst);
	} else {
		if (!BusArr[inst]) BusArr[inst] = BusInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Busmutex);
#endif
	if (!BusArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	uint ret = BusArr[inst]->BitsGet32(BusArr[inst],arg0,arg1,arg2);
	Output32(oi,"BitsGet32",ret);
}
prototype protBus34 = {
	NetBus_BitsGet32,
	ArrayL(reqtypesBus34),ArrayL(replytypesBus34),
	BusCommand34
};


Time** TimeArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t Timemutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// uint Wait(void *me,uint);
// Wait <uint>
// ->
// <uint>
ArrayAuto(int,reqtypesTime1,ARR(32));
ArrayAuto(int,replytypesTime1,ARR(32));
void TimeCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Timemutex);
#endif
	if (!TimeArr) {
		TimeArr = ArrayAlloc(inst+1,sizeof(Time *));
		for (i=0;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i]= TimeInit(inst);
	} else if (inst >= ArrayLength(TimeArr)) {
		i = ArrayLength(TimeArr);
		TimeArr = ArraySize(TimeArr,inst+1);
		for (;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i] = TimeInit(inst);
	} else {
		if (!TimeArr[inst]) TimeArr[inst] = TimeInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Timemutex);
#endif
	if (!TimeArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	uint ret = TimeArr[inst]->Wait(TimeArr[inst],arg0);
	Output32(oi,"Wait",ret);
}
prototype protTime1 = {
	NetTime_Wait,
	ArrayL(reqtypesTime1),ArrayL(replytypesTime1),
	TimeCommand1
};

// void Delay(void *me,uint);
// Delay <uint>
// ->
//
ArrayAuto(int,reqtypesTime2,ARR(32));
ArrayAuto(int,replytypesTime2,ARR());
void TimeCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Timemutex);
#endif
	if (!TimeArr) {
		TimeArr = ArrayAlloc(inst+1,sizeof(Time *));
		for (i=0;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i]= TimeInit(inst);
	} else if (inst >= ArrayLength(TimeArr)) {
		i = ArrayLength(TimeArr);
		TimeArr = ArraySize(TimeArr,inst+1);
		for (;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i] = TimeInit(inst);
	} else {
		if (!TimeArr[inst]) TimeArr[inst] = TimeInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Timemutex);
#endif
	if (!TimeArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	TimeArr[inst]->Delay(TimeArr[inst],arg0);
}
prototype protTime2 = {
	NetTime_Delay,
	ArrayL(reqtypesTime2),ArrayL(replytypesTime2),
	TimeCommand2
};

// uint Tick(void *me);
// Tick
// ->
// <uint>
ArrayAuto(int,reqtypesTime3,ARR());
ArrayAuto(int,replytypesTime3,ARR(32));
void TimeCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Timemutex);
#endif
	if (!TimeArr) {
		TimeArr = ArrayAlloc(inst+1,sizeof(Time *));
		for (i=0;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i]= TimeInit(inst);
	} else if (inst >= ArrayLength(TimeArr)) {
		i = ArrayLength(TimeArr);
		TimeArr = ArraySize(TimeArr,inst+1);
		for (;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i] = TimeInit(inst);
	} else {
		if (!TimeArr[inst]) TimeArr[inst] = TimeInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Timemutex);
#endif
	if (!TimeArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint ret = TimeArr[inst]->Tick(TimeArr[inst]);
	Output32(oi,"Tick",ret);
}
prototype protTime3 = {
	NetTime_Tick,
	ArrayL(reqtypesTime3),ArrayL(replytypesTime3),
	TimeCommand3
};

// uint usElapsed(void *me,uint);
// usElapsed <uint>
// ->
// <uint>
ArrayAuto(int,reqtypesTime4,ARR(32));
ArrayAuto(int,replytypesTime4,ARR(32));
void TimeCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Timemutex);
#endif
	if (!TimeArr) {
		TimeArr = ArrayAlloc(inst+1,sizeof(Time *));
		for (i=0;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i]= TimeInit(inst);
	} else if (inst >= ArrayLength(TimeArr)) {
		i = ArrayLength(TimeArr);
		TimeArr = ArraySize(TimeArr,inst+1);
		for (;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i] = TimeInit(inst);
	} else {
		if (!TimeArr[inst]) TimeArr[inst] = TimeInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Timemutex);
#endif
	if (!TimeArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	uint ret = TimeArr[inst]->usElapsed(TimeArr[inst],arg0);
	Output32(oi,"usElapsed",ret);
}
prototype protTime4 = {
	NetTime_usElapsed,
	ArrayL(reqtypesTime4),ArrayL(replytypesTime4),
	TimeCommand4
};

// uint usFuture(void *me,uint,uint);
// usFuture <uint> <uint>
// ->
// <uint>
ArrayAuto(int,reqtypesTime5,ARR(32,32));
ArrayAuto(int,replytypesTime5,ARR(32));
void TimeCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Timemutex);
#endif
	if (!TimeArr) {
		TimeArr = ArrayAlloc(inst+1,sizeof(Time *));
		for (i=0;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i]= TimeInit(inst);
	} else if (inst >= ArrayLength(TimeArr)) {
		i = ArrayLength(TimeArr);
		TimeArr = ArraySize(TimeArr,inst+1);
		for (;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i] = TimeInit(inst);
	} else {
		if (!TimeArr[inst]) TimeArr[inst] = TimeInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Timemutex);
#endif
	if (!TimeArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	uint arg1 = Input32(argv[1]);
	uint ret = TimeArr[inst]->usFuture(TimeArr[inst],arg0,arg1);
	Output32(oi,"usFuture",ret);
}
prototype protTime5 = {
	NetTime_usFuture,
	ArrayL(reqtypesTime5),ArrayL(replytypesTime5),
	TimeCommand5
};

// int TimeoutQ(void *me,uint,uint);
// TimeoutQ <uint> <uint>
// ->
// <int>
ArrayAuto(int,reqtypesTime6,ARR(32,32));
ArrayAuto(int,replytypesTime6,ARR(-32));
void TimeCommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Timemutex);
#endif
	if (!TimeArr) {
		TimeArr = ArrayAlloc(inst+1,sizeof(Time *));
		for (i=0;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i]= TimeInit(inst);
	} else if (inst >= ArrayLength(TimeArr)) {
		i = ArrayLength(TimeArr);
		TimeArr = ArraySize(TimeArr,inst+1);
		for (;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i] = TimeInit(inst);
	} else {
		if (!TimeArr[inst]) TimeArr[inst] = TimeInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Timemutex);
#endif
	if (!TimeArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	uint arg1 = Input32(argv[1]);
	int ret = TimeArr[inst]->TimeoutQ(TimeArr[inst],arg0,arg1);
	Output_32(oi,"TimeoutQ",ret);
}
prototype protTime6 = {
	NetTime_TimeoutQ,
	ArrayL(reqtypesTime6),ArrayL(replytypesTime6),
	TimeCommand6
};

// uint TPS(void *me);
// TPS
// ->
// <uint>
ArrayAuto(int,reqtypesTime7,ARR());
ArrayAuto(int,replytypesTime7,ARR(32));
void TimeCommand7(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Timemutex);
#endif
	if (!TimeArr) {
		TimeArr = ArrayAlloc(inst+1,sizeof(Time *));
		for (i=0;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i]= TimeInit(inst);
	} else if (inst >= ArrayLength(TimeArr)) {
		i = ArrayLength(TimeArr);
		TimeArr = ArraySize(TimeArr,inst+1);
		for (;i<inst;i++) TimeArr[i] = 0;
		TimeArr[i] = TimeInit(inst);
	} else {
		if (!TimeArr[inst]) TimeArr[inst] = TimeInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Timemutex);
#endif
	if (!TimeArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint ret = TimeArr[inst]->TPS(TimeArr[inst]);
	Output32(oi,"TPS",ret);
}
prototype protTime7 = {
	NetTime_TPS,
	ArrayL(reqtypesTime7),ArrayL(replytypesTime7),
	TimeCommand7
};


Pin** PinArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t Pinmutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Lock(void *me,uint,int);
// Lock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesPin1,ARR(32,-32));
ArrayAuto(int,replytypesPin1,ARR(-32));
void PinCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Pinmutex);
#endif
	if (!PinArr) {
		PinArr = ArrayAlloc(inst+1,sizeof(Pin *));
		for (i=0;i<inst;i++) PinArr[i] = 0;
		PinArr[i]= PinInit(inst);
	} else if (inst >= ArrayLength(PinArr)) {
		i = ArrayLength(PinArr);
		PinArr = ArraySize(PinArr,inst+1);
		for (;i<inst;i++) PinArr[i] = 0;
		PinArr[i] = PinInit(inst);
	} else {
		if (!PinArr[inst]) PinArr[inst] = PinInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Pinmutex);
#endif
	if (!PinArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = PinArr[inst]->Lock(PinArr[inst],arg0,arg1);
	Output_32(oi,"Lock",ret);
}
prototype protPin1 = {
	NetPin_Lock,
	ArrayL(reqtypesPin1),ArrayL(replytypesPin1),
	PinCommand1
};

// int Unlock(void *me,uint,int);
// Unlock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesPin2,ARR(32,-32));
ArrayAuto(int,replytypesPin2,ARR(-32));
void PinCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Pinmutex);
#endif
	if (!PinArr) {
		PinArr = ArrayAlloc(inst+1,sizeof(Pin *));
		for (i=0;i<inst;i++) PinArr[i] = 0;
		PinArr[i]= PinInit(inst);
	} else if (inst >= ArrayLength(PinArr)) {
		i = ArrayLength(PinArr);
		PinArr = ArraySize(PinArr,inst+1);
		for (;i<inst;i++) PinArr[i] = 0;
		PinArr[i] = PinInit(inst);
	} else {
		if (!PinArr[inst]) PinArr[inst] = PinInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Pinmutex);
#endif
	if (!PinArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = PinArr[inst]->Unlock(PinArr[inst],arg0,arg1);
	Output_32(oi,"Unlock",ret);
}
prototype protPin2 = {
	NetPin_Unlock,
	ArrayL(reqtypesPin2),ArrayL(replytypesPin2),
	PinCommand2
};

// int Preempt(void *me);
// Preempt
// ->
// <int>
ArrayAuto(int,reqtypesPin3,ARR());
ArrayAuto(int,replytypesPin3,ARR(-32));
void PinCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Pinmutex);
#endif
	if (!PinArr) {
		PinArr = ArrayAlloc(inst+1,sizeof(Pin *));
		for (i=0;i<inst;i++) PinArr[i] = 0;
		PinArr[i]= PinInit(inst);
	} else if (inst >= ArrayLength(PinArr)) {
		i = ArrayLength(PinArr);
		PinArr = ArraySize(PinArr,inst+1);
		for (;i<inst;i++) PinArr[i] = 0;
		PinArr[i] = PinInit(inst);
	} else {
		if (!PinArr[inst]) PinArr[inst] = PinInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Pinmutex);
#endif
	if (!PinArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = PinArr[inst]->Preempt(PinArr[inst]);
	Output_32(oi,"Preempt",ret);
}
prototype protPin3 = {
	NetPin_Preempt,
	ArrayL(reqtypesPin3),ArrayL(replytypesPin3),
	PinCommand3
};

// PinMode ModeGet(void *me,int);
// ModeGet <int>
// ->
// <PinMode>
ArrayAuto(int,reqtypesPin4,ARR(-32));
ArrayAuto(int,replytypesPin4,ARR(1000005));
void PinCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Pinmutex);
#endif
	if (!PinArr) {
		PinArr = ArrayAlloc(inst+1,sizeof(Pin *));
		for (i=0;i<inst;i++) PinArr[i] = 0;
		PinArr[i]= PinInit(inst);
	} else if (inst >= ArrayLength(PinArr)) {
		i = ArrayLength(PinArr);
		PinArr = ArraySize(PinArr,inst+1);
		for (;i<inst;i++) PinArr[i] = 0;
		PinArr[i] = PinInit(inst);
	} else {
		if (!PinArr[inst]) PinArr[inst] = PinInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Pinmutex);
#endif
	if (!PinArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	PinMode ret = PinArr[inst]->ModeGet(PinArr[inst],arg0);
	Output1000005(oi,"ModeGet",ret);
}
prototype protPin4 = {
	NetPin_ModeGet,
	ArrayL(reqtypesPin4),ArrayL(replytypesPin4),
	PinCommand4
};

// int ModeSet(void *me,int,int);
// ModeSet <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesPin5,ARR(-32,-32));
ArrayAuto(int,replytypesPin5,ARR(-32));
void PinCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&Pinmutex);
#endif
	if (!PinArr) {
		PinArr = ArrayAlloc(inst+1,sizeof(Pin *));
		for (i=0;i<inst;i++) PinArr[i] = 0;
		PinArr[i]= PinInit(inst);
	} else if (inst >= ArrayLength(PinArr)) {
		i = ArrayLength(PinArr);
		PinArr = ArraySize(PinArr,inst+1);
		for (;i<inst;i++) PinArr[i] = 0;
		PinArr[i] = PinInit(inst);
	} else {
		if (!PinArr[inst]) PinArr[inst] = PinInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&Pinmutex);
#endif
	if (!PinArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = PinArr[inst]->ModeSet(PinArr[inst],arg0,arg1);
	Output_32(oi,"ModeSet",ret);
}
prototype protPin5 = {
	NetPin_ModeSet,
	ArrayL(reqtypesPin5),ArrayL(replytypesPin5),
	PinCommand5
};


DIORaw** DIORawArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t DIORawmutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Lock(void *me,uint,int);
// Lock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesDIORaw1,ARR(32,-32));
ArrayAuto(int,replytypesDIORaw1,ARR(-32));
void DIORawCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIORawmutex);
#endif
	if (!DIORawArr) {
		DIORawArr = ArrayAlloc(inst+1,sizeof(DIORaw *));
		for (i=0;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i]= DIORawInit(inst);
	} else if (inst >= ArrayLength(DIORawArr)) {
		i = ArrayLength(DIORawArr);
		DIORawArr = ArraySize(DIORawArr,inst+1);
		for (;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i] = DIORawInit(inst);
	} else {
		if (!DIORawArr[inst]) DIORawArr[inst] = DIORawInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIORawmutex);
#endif
	if (!DIORawArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = DIORawArr[inst]->Lock(DIORawArr[inst],arg0,arg1);
	Output_32(oi,"Lock",ret);
}
prototype protDIORaw1 = {
	NetDIORaw_Lock,
	ArrayL(reqtypesDIORaw1),ArrayL(replytypesDIORaw1),
	DIORawCommand1
};

// int Unlock(void *me,uint,int);
// Unlock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesDIORaw2,ARR(32,-32));
ArrayAuto(int,replytypesDIORaw2,ARR(-32));
void DIORawCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIORawmutex);
#endif
	if (!DIORawArr) {
		DIORawArr = ArrayAlloc(inst+1,sizeof(DIORaw *));
		for (i=0;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i]= DIORawInit(inst);
	} else if (inst >= ArrayLength(DIORawArr)) {
		i = ArrayLength(DIORawArr);
		DIORawArr = ArraySize(DIORawArr,inst+1);
		for (;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i] = DIORawInit(inst);
	} else {
		if (!DIORawArr[inst]) DIORawArr[inst] = DIORawInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIORawmutex);
#endif
	if (!DIORawArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = DIORawArr[inst]->Unlock(DIORawArr[inst],arg0,arg1);
	Output_32(oi,"Unlock",ret);
}
prototype protDIORaw2 = {
	NetDIORaw_Unlock,
	ArrayL(reqtypesDIORaw2),ArrayL(replytypesDIORaw2),
	DIORawCommand2
};

// int Preempt(void *me);
// Preempt
// ->
// <int>
ArrayAuto(int,reqtypesDIORaw3,ARR());
ArrayAuto(int,replytypesDIORaw3,ARR(-32));
void DIORawCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIORawmutex);
#endif
	if (!DIORawArr) {
		DIORawArr = ArrayAlloc(inst+1,sizeof(DIORaw *));
		for (i=0;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i]= DIORawInit(inst);
	} else if (inst >= ArrayLength(DIORawArr)) {
		i = ArrayLength(DIORawArr);
		DIORawArr = ArraySize(DIORawArr,inst+1);
		for (;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i] = DIORawInit(inst);
	} else {
		if (!DIORawArr[inst]) DIORawArr[inst] = DIORawInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIORawmutex);
#endif
	if (!DIORawArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = DIORawArr[inst]->Preempt(DIORawArr[inst]);
	Output_32(oi,"Preempt",ret);
}
prototype protDIORaw3 = {
	NetDIORaw_Preempt,
	ArrayL(reqtypesDIORaw3),ArrayL(replytypesDIORaw3),
	DIORawCommand3
};

// void DirSet(void *me,int,int);
// DirSet <int> <int>
// ->
//
ArrayAuto(int,reqtypesDIORaw4,ARR(-32,-32));
ArrayAuto(int,replytypesDIORaw4,ARR());
void DIORawCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIORawmutex);
#endif
	if (!DIORawArr) {
		DIORawArr = ArrayAlloc(inst+1,sizeof(DIORaw *));
		for (i=0;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i]= DIORawInit(inst);
	} else if (inst >= ArrayLength(DIORawArr)) {
		i = ArrayLength(DIORawArr);
		DIORawArr = ArraySize(DIORawArr,inst+1);
		for (;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i] = DIORawInit(inst);
	} else {
		if (!DIORawArr[inst]) DIORawArr[inst] = DIORawInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIORawmutex);
#endif
	if (!DIORawArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	DIORawArr[inst]->DirSet(DIORawArr[inst],arg0,arg1);
}
prototype protDIORaw4 = {
	NetDIORaw_DirSet,
	ArrayL(reqtypesDIORaw4),ArrayL(replytypesDIORaw4),
	DIORawCommand4
};

// void DataSet(void *me,int,int);
// DataSet <int> <int>
// ->
//
ArrayAuto(int,reqtypesDIORaw5,ARR(-32,-32));
ArrayAuto(int,replytypesDIORaw5,ARR());
void DIORawCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIORawmutex);
#endif
	if (!DIORawArr) {
		DIORawArr = ArrayAlloc(inst+1,sizeof(DIORaw *));
		for (i=0;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i]= DIORawInit(inst);
	} else if (inst >= ArrayLength(DIORawArr)) {
		i = ArrayLength(DIORawArr);
		DIORawArr = ArraySize(DIORawArr,inst+1);
		for (;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i] = DIORawInit(inst);
	} else {
		if (!DIORawArr[inst]) DIORawArr[inst] = DIORawInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIORawmutex);
#endif
	if (!DIORawArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	DIORawArr[inst]->DataSet(DIORawArr[inst],arg0,arg1);
}
prototype protDIORaw5 = {
	NetDIORaw_DataSet,
	ArrayL(reqtypesDIORaw5),ArrayL(replytypesDIORaw5),
	DIORawCommand5
};

// int DirGet(void *me,int);
// DirGet <int>
// ->
// <int>
ArrayAuto(int,reqtypesDIORaw6,ARR(-32));
ArrayAuto(int,replytypesDIORaw6,ARR(-32));
void DIORawCommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIORawmutex);
#endif
	if (!DIORawArr) {
		DIORawArr = ArrayAlloc(inst+1,sizeof(DIORaw *));
		for (i=0;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i]= DIORawInit(inst);
	} else if (inst >= ArrayLength(DIORawArr)) {
		i = ArrayLength(DIORawArr);
		DIORawArr = ArraySize(DIORawArr,inst+1);
		for (;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i] = DIORawInit(inst);
	} else {
		if (!DIORawArr[inst]) DIORawArr[inst] = DIORawInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIORawmutex);
#endif
	if (!DIORawArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = DIORawArr[inst]->DirGet(DIORawArr[inst],arg0);
	Output_32(oi,"DirGet",ret);
}
prototype protDIORaw6 = {
	NetDIORaw_DirGet,
	ArrayL(reqtypesDIORaw6),ArrayL(replytypesDIORaw6),
	DIORawCommand6
};

// int DataGet(void *me,int);
// DataGet <int>
// ->
// <int>
ArrayAuto(int,reqtypesDIORaw7,ARR(-32));
ArrayAuto(int,replytypesDIORaw7,ARR(-32));
void DIORawCommand7(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIORawmutex);
#endif
	if (!DIORawArr) {
		DIORawArr = ArrayAlloc(inst+1,sizeof(DIORaw *));
		for (i=0;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i]= DIORawInit(inst);
	} else if (inst >= ArrayLength(DIORawArr)) {
		i = ArrayLength(DIORawArr);
		DIORawArr = ArraySize(DIORawArr,inst+1);
		for (;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i] = DIORawInit(inst);
	} else {
		if (!DIORawArr[inst]) DIORawArr[inst] = DIORawInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIORawmutex);
#endif
	if (!DIORawArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = DIORawArr[inst]->DataGet(DIORawArr[inst],arg0);
	Output_32(oi,"DataGet",ret);
}
prototype protDIORaw7 = {
	NetDIORaw_DataGet,
	ArrayL(reqtypesDIORaw7),ArrayL(replytypesDIORaw7),
	DIORawCommand7
};

// uint Count(void *me);
// Count
// ->
// <uint>
ArrayAuto(int,reqtypesDIORaw8,ARR());
ArrayAuto(int,replytypesDIORaw8,ARR(32));
void DIORawCommand8(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIORawmutex);
#endif
	if (!DIORawArr) {
		DIORawArr = ArrayAlloc(inst+1,sizeof(DIORaw *));
		for (i=0;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i]= DIORawInit(inst);
	} else if (inst >= ArrayLength(DIORawArr)) {
		i = ArrayLength(DIORawArr);
		DIORawArr = ArraySize(DIORawArr,inst+1);
		for (;i<inst;i++) DIORawArr[i] = 0;
		DIORawArr[i] = DIORawInit(inst);
	} else {
		if (!DIORawArr[inst]) DIORawArr[inst] = DIORawInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIORawmutex);
#endif
	if (!DIORawArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint ret = DIORawArr[inst]->Count(DIORawArr[inst]);
	Output32(oi,"Count",ret);
}
prototype protDIORaw8 = {
	NetDIORaw_Count,
	ArrayL(reqtypesDIORaw8),ArrayL(replytypesDIORaw8),
	DIORawCommand8
};


DIO** DIOArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t DIOmutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Lock(void *me,uint,int);
// Lock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesDIO1,ARR(32,-32));
ArrayAuto(int,replytypesDIO1,ARR(-32));
void DIOCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = DIOArr[inst]->Lock(DIOArr[inst],arg0,arg1);
	Output_32(oi,"Lock",ret);
}
prototype protDIO1 = {
	NetDIO_Lock,
	ArrayL(reqtypesDIO1),ArrayL(replytypesDIO1),
	DIOCommand1
};

// int Unlock(void *me,uint,int);
// Unlock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesDIO2,ARR(32,-32));
ArrayAuto(int,replytypesDIO2,ARR(-32));
void DIOCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = DIOArr[inst]->Unlock(DIOArr[inst],arg0,arg1);
	Output_32(oi,"Unlock",ret);
}
prototype protDIO2 = {
	NetDIO_Unlock,
	ArrayL(reqtypesDIO2),ArrayL(replytypesDIO2),
	DIOCommand2
};

// int Preempt(void *me);
// Preempt
// ->
// <int>
ArrayAuto(int,reqtypesDIO3,ARR());
ArrayAuto(int,replytypesDIO3,ARR(-32));
void DIOCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = DIOArr[inst]->Preempt(DIOArr[inst]);
	Output_32(oi,"Preempt",ret);
}
prototype protDIO3 = {
	NetDIO_Preempt,
	ArrayL(reqtypesDIO3),ArrayL(replytypesDIO3),
	DIOCommand3
};

// void Refresh(void *me);
// Refresh
// ->
//
ArrayAuto(int,reqtypesDIO4,ARR());
ArrayAuto(int,replytypesDIO4,ARR());
void DIOCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	DIOArr[inst]->Refresh(DIOArr[inst]);
}
prototype protDIO4 = {
	NetDIO_Refresh,
	ArrayL(reqtypesDIO4),ArrayL(replytypesDIO4),
	DIOCommand4
};

// void Commit(void *me,int);
// Commit <int>
// ->
//
ArrayAuto(int,reqtypesDIO5,ARR(-32));
ArrayAuto(int,replytypesDIO5,ARR());
void DIOCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	DIOArr[inst]->Commit(DIOArr[inst],arg0);
}
prototype protDIO5 = {
	NetDIO_Commit,
	ArrayL(reqtypesDIO5),ArrayL(replytypesDIO5),
	DIOCommand5
};

// void Set(void *me,int,int);
// Set <int> <int>
// ->
//
ArrayAuto(int,reqtypesDIO6,ARR(-32,-32));
ArrayAuto(int,replytypesDIO6,ARR());
void DIOCommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	DIOArr[inst]->Set(DIOArr[inst],arg0,arg1);
}
prototype protDIO6 = {
	NetDIO_Set,
	ArrayL(reqtypesDIO6),ArrayL(replytypesDIO6),
	DIOCommand6
};

// DIOState Get(void *me,int);
// Get <int>
// ->
// <DIOState>
ArrayAuto(int,reqtypesDIO7,ARR(-32));
ArrayAuto(int,replytypesDIO7,ARR(1000003));
void DIOCommand7(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	DIOState ret = DIOArr[inst]->Get(DIOArr[inst],arg0);
	Output1000003(oi,"Get",ret);
}
prototype protDIO7 = {
	NetDIO_Get,
	ArrayL(reqtypesDIO7),ArrayL(replytypesDIO7),
	DIOCommand7
};

// void SetAsync(void *me,int,int);
// SetAsync <int> <int>
// ->
//
ArrayAuto(int,reqtypesDIO8,ARR(-32,-32));
ArrayAuto(int,replytypesDIO8,ARR());
void DIOCommand8(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	DIOArr[inst]->SetAsync(DIOArr[inst],arg0,arg1);
}
prototype protDIO8 = {
	NetDIO_SetAsync,
	ArrayL(reqtypesDIO8),ArrayL(replytypesDIO8),
	DIOCommand8
};

// DIOState GetAsync(void *me,int);
// GetAsync <int>
// ->
// <DIOState>
ArrayAuto(int,reqtypesDIO9,ARR(-32));
ArrayAuto(int,replytypesDIO9,ARR(1000003));
void DIOCommand9(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	DIOState ret = DIOArr[inst]->GetAsync(DIOArr[inst],arg0);
	Output1000003(oi,"GetAsync",ret);
}
prototype protDIO9 = {
	NetDIO_GetAsync,
	ArrayL(reqtypesDIO9),ArrayL(replytypesDIO9),
	DIOCommand9
};

// void Wait(void *me,int*,int,int,const int*,const int*);
// Wait <int> <int> <int*> <int*>
// ->
// <int*>
ArrayAuto(int,reqtypesDIO10,ARR(-32,-32,-1032,-1032));
ArrayAuto(int,replytypesDIO10,ARR(-1032));
void DIOCommand10(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int* arg0 = ArrayAlloc(Input32(argv[0]),sizeof(int));
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	const int* arg3 = Input_1032(argv[3]);
	const int* arg4 = Input_1032(argv[4]);
	DIOArr[inst]->Wait(DIOArr[inst],arg0,arg1,arg2,arg3,arg4);
	Output_1032(oi,"Wait",arg0);
	ArrayFree(arg0);
	ArrayFree(arg3);
	ArrayFree(arg4);
}
prototype protDIO10 = {
	NetDIO_Wait,
	ArrayL(reqtypesDIO10),ArrayL(replytypesDIO10),
	DIOCommand10
};

// uint Count(void *me);
// Count
// ->
// <uint>
ArrayAuto(int,reqtypesDIO11,ARR());
ArrayAuto(int,replytypesDIO11,ARR(32));
void DIOCommand11(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint ret = DIOArr[inst]->Count(DIOArr[inst]);
	Output32(oi,"Count",ret);
}
prototype protDIO11 = {
	NetDIO_Count,
	ArrayL(reqtypesDIO11),ArrayL(replytypesDIO11),
	DIOCommand11
};

// DIOCaps Capabilities(void *me,uint);
// Capabilities <uint>
// ->
// <DIOCaps>
ArrayAuto(int,reqtypesDIO12,ARR(32));
ArrayAuto(int,replytypesDIO12,ARR(1000004));
void DIOCommand12(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	DIOCaps ret = DIOArr[inst]->Capabilities(DIOArr[inst],arg0);
	Output1000004(oi,"Capabilities",ret);
}
prototype protDIO12 = {
	NetDIO_Capabilities,
	ArrayL(reqtypesDIO12),ArrayL(replytypesDIO12),
	DIOCommand12
};

// int GetMulti(void *me,char*,int);
// GetMulti <int>
// ->
// <int> <char*>
ArrayAuto(int,reqtypesDIO13,ARR(-32));
ArrayAuto(int,replytypesDIO13,ARR(-32,-1008));
void DIOCommand13(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&DIOmutex);
#endif
	if (!DIOArr) {
		DIOArr = ArrayAlloc(inst+1,sizeof(DIO *));
		for (i=0;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i]= DIOInit(inst);
	} else if (inst >= ArrayLength(DIOArr)) {
		i = ArrayLength(DIOArr);
		DIOArr = ArraySize(DIOArr,inst+1);
		for (;i<inst;i++) DIOArr[i] = 0;
		DIOArr[i] = DIOInit(inst);
	} else {
		if (!DIOArr[inst]) DIOArr[inst] = DIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&DIOmutex);
#endif
	if (!DIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	char* arg0 = ArrayAlloc(Input32(argv[0]),sizeof(char));
	int arg1 = Input_32(argv[1]);
	int ret = DIOArr[inst]->GetMulti(DIOArr[inst],arg0,arg1);
	Output_32(oi,"GetMulti",ret);
	Output_1008(oi,"GetMulti",arg0);
	ArrayFree(arg0);
}
prototype protDIO13 = {
	NetDIO_GetMulti,
	ArrayL(reqtypesDIO13),ArrayL(replytypesDIO13),
	DIOCommand13
};


TWI** TWIArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t TWImutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Lock(void *me,uint,int);
// Lock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesTWI1,ARR(32,-32));
ArrayAuto(int,replytypesTWI1,ARR(-32));
void TWICommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&TWImutex);
#endif
	if (!TWIArr) {
		TWIArr = ArrayAlloc(inst+1,sizeof(TWI *));
		for (i=0;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i]= TWIInit(inst);
	} else if (inst >= ArrayLength(TWIArr)) {
		i = ArrayLength(TWIArr);
		TWIArr = ArraySize(TWIArr,inst+1);
		for (;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i] = TWIInit(inst);
	} else {
		if (!TWIArr[inst]) TWIArr[inst] = TWIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&TWImutex);
#endif
	if (!TWIArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = TWIArr[inst]->Lock(TWIArr[inst],arg0,arg1);
	Output_32(oi,"Lock",ret);
}
prototype protTWI1 = {
	NetTWI_Lock,
	ArrayL(reqtypesTWI1),ArrayL(replytypesTWI1),
	TWICommand1
};

// int Unlock(void *me,uint,int);
// Unlock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesTWI2,ARR(32,-32));
ArrayAuto(int,replytypesTWI2,ARR(-32));
void TWICommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&TWImutex);
#endif
	if (!TWIArr) {
		TWIArr = ArrayAlloc(inst+1,sizeof(TWI *));
		for (i=0;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i]= TWIInit(inst);
	} else if (inst >= ArrayLength(TWIArr)) {
		i = ArrayLength(TWIArr);
		TWIArr = ArraySize(TWIArr,inst+1);
		for (;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i] = TWIInit(inst);
	} else {
		if (!TWIArr[inst]) TWIArr[inst] = TWIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&TWImutex);
#endif
	if (!TWIArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = TWIArr[inst]->Unlock(TWIArr[inst],arg0,arg1);
	Output_32(oi,"Unlock",ret);
}
prototype protTWI2 = {
	NetTWI_Unlock,
	ArrayL(reqtypesTWI2),ArrayL(replytypesTWI2),
	TWICommand2
};

// int Preempt(void *me);
// Preempt
// ->
// <int>
ArrayAuto(int,reqtypesTWI3,ARR());
ArrayAuto(int,replytypesTWI3,ARR(-32));
void TWICommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&TWImutex);
#endif
	if (!TWIArr) {
		TWIArr = ArrayAlloc(inst+1,sizeof(TWI *));
		for (i=0;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i]= TWIInit(inst);
	} else if (inst >= ArrayLength(TWIArr)) {
		i = ArrayLength(TWIArr);
		TWIArr = ArraySize(TWIArr,inst+1);
		for (;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i] = TWIInit(inst);
	} else {
		if (!TWIArr[inst]) TWIArr[inst] = TWIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&TWImutex);
#endif
	if (!TWIArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = TWIArr[inst]->Preempt(TWIArr[inst]);
	Output_32(oi,"Preempt",ret);
}
prototype protTWI3 = {
	NetTWI_Preempt,
	ArrayL(reqtypesTWI3),ArrayL(replytypesTWI3),
	TWICommand3
};

// int Write(void *me,int,int,int,const char*);
// Write <int> <int> <int> <char*>
// ->
// <int>
ArrayAuto(int,reqtypesTWI4,ARR(-32,-32,-32,-1008));
ArrayAuto(int,replytypesTWI4,ARR(-32));
void TWICommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&TWImutex);
#endif
	if (!TWIArr) {
		TWIArr = ArrayAlloc(inst+1,sizeof(TWI *));
		for (i=0;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i]= TWIInit(inst);
	} else if (inst >= ArrayLength(TWIArr)) {
		i = ArrayLength(TWIArr);
		TWIArr = ArraySize(TWIArr,inst+1);
		for (;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i] = TWIInit(inst);
	} else {
		if (!TWIArr[inst]) TWIArr[inst] = TWIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&TWImutex);
#endif
	if (!TWIArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	const char* arg3 = Input_1008(argv[3]);
	int ret = TWIArr[inst]->Write(TWIArr[inst],arg0,arg1,arg2,arg3);
	Output_32(oi,"Write",ret);
	ArrayFree(arg3);
}
prototype protTWI4 = {
	NetTWI_Write,
	ArrayL(reqtypesTWI4),ArrayL(replytypesTWI4),
	TWICommand4
};

// int Read(void *me,int,int,int,char*);
// Read <int> <int> <int>
// ->
// <int> <char*>
ArrayAuto(int,reqtypesTWI5,ARR(-32,-32,-32));
ArrayAuto(int,replytypesTWI5,ARR(-32,-1008));
void TWICommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&TWImutex);
#endif
	if (!TWIArr) {
		TWIArr = ArrayAlloc(inst+1,sizeof(TWI *));
		for (i=0;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i]= TWIInit(inst);
	} else if (inst >= ArrayLength(TWIArr)) {
		i = ArrayLength(TWIArr);
		TWIArr = ArraySize(TWIArr,inst+1);
		for (;i<inst;i++) TWIArr[i] = 0;
		TWIArr[i] = TWIInit(inst);
	} else {
		if (!TWIArr[inst]) TWIArr[inst] = TWIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&TWImutex);
#endif
	if (!TWIArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int arg2 = Input_32(argv[2]);
	char* arg3 = ArrayAlloc(Input32(argv[3]),sizeof(char));
	int ret = TWIArr[inst]->Read(TWIArr[inst],arg0,arg1,arg2,arg3);
	Output_32(oi,"Read",ret);
	Output_1008(oi,"Read",arg3);
	ArrayFree(arg3);
}
prototype protTWI5 = {
	NetTWI_Read,
	ArrayL(reqtypesTWI5),ArrayL(replytypesTWI5),
	TWICommand5
};


SPI** SPIArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t SPImutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Lock(void *me,uint,int);
// Lock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesSPI1,ARR(32,-32));
ArrayAuto(int,replytypesSPI1,ARR(-32));
void SPICommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&SPImutex);
#endif
	if (!SPIArr) {
		SPIArr = ArrayAlloc(inst+1,sizeof(SPI *));
		for (i=0;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i]= SPIInit(inst);
	} else if (inst >= ArrayLength(SPIArr)) {
		i = ArrayLength(SPIArr);
		SPIArr = ArraySize(SPIArr,inst+1);
		for (;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i] = SPIInit(inst);
	} else {
		if (!SPIArr[inst]) SPIArr[inst] = SPIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&SPImutex);
#endif
	if (!SPIArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = SPIArr[inst]->Lock(SPIArr[inst],arg0,arg1);
	Output_32(oi,"Lock",ret);
}
prototype protSPI1 = {
	NetSPI_Lock,
	ArrayL(reqtypesSPI1),ArrayL(replytypesSPI1),
	SPICommand1
};

// int Unlock(void *me,uint,int);
// Unlock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesSPI2,ARR(32,-32));
ArrayAuto(int,replytypesSPI2,ARR(-32));
void SPICommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&SPImutex);
#endif
	if (!SPIArr) {
		SPIArr = ArrayAlloc(inst+1,sizeof(SPI *));
		for (i=0;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i]= SPIInit(inst);
	} else if (inst >= ArrayLength(SPIArr)) {
		i = ArrayLength(SPIArr);
		SPIArr = ArraySize(SPIArr,inst+1);
		for (;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i] = SPIInit(inst);
	} else {
		if (!SPIArr[inst]) SPIArr[inst] = SPIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&SPImutex);
#endif
	if (!SPIArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = SPIArr[inst]->Unlock(SPIArr[inst],arg0,arg1);
	Output_32(oi,"Unlock",ret);
}
prototype protSPI2 = {
	NetSPI_Unlock,
	ArrayL(reqtypesSPI2),ArrayL(replytypesSPI2),
	SPICommand2
};

// int Preempt(void *me);
// Preempt
// ->
// <int>
ArrayAuto(int,reqtypesSPI3,ARR());
ArrayAuto(int,replytypesSPI3,ARR(-32));
void SPICommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&SPImutex);
#endif
	if (!SPIArr) {
		SPIArr = ArrayAlloc(inst+1,sizeof(SPI *));
		for (i=0;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i]= SPIInit(inst);
	} else if (inst >= ArrayLength(SPIArr)) {
		i = ArrayLength(SPIArr);
		SPIArr = ArraySize(SPIArr,inst+1);
		for (;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i] = SPIInit(inst);
	} else {
		if (!SPIArr[inst]) SPIArr[inst] = SPIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&SPImutex);
#endif
	if (!SPIArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = SPIArr[inst]->Preempt(SPIArr[inst]);
	Output_32(oi,"Preempt",ret);
}
prototype protSPI3 = {
	NetSPI_Preempt,
	ArrayL(reqtypesSPI3),ArrayL(replytypesSPI3),
	SPICommand3
};

// int Write(void *me,int,const char*);
// Write <int> <char*>
// ->
// <int>
ArrayAuto(int,reqtypesSPI4,ARR(-32,-1008));
ArrayAuto(int,replytypesSPI4,ARR(-32));
void SPICommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&SPImutex);
#endif
	if (!SPIArr) {
		SPIArr = ArrayAlloc(inst+1,sizeof(SPI *));
		for (i=0;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i]= SPIInit(inst);
	} else if (inst >= ArrayLength(SPIArr)) {
		i = ArrayLength(SPIArr);
		SPIArr = ArraySize(SPIArr,inst+1);
		for (;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i] = SPIInit(inst);
	} else {
		if (!SPIArr[inst]) SPIArr[inst] = SPIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&SPImutex);
#endif
	if (!SPIArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	const char* arg1 = Input_1008(argv[1]);
	int ret = SPIArr[inst]->Write(SPIArr[inst],arg0,arg1);
	Output_32(oi,"Write",ret);
	ArrayFree(arg1);
}
prototype protSPI4 = {
	NetSPI_Write,
	ArrayL(reqtypesSPI4),ArrayL(replytypesSPI4),
	SPICommand4
};

// int Read(void *me,int,char*);
// Read <int>
// ->
// <int> <char*>
ArrayAuto(int,reqtypesSPI5,ARR(-32));
ArrayAuto(int,replytypesSPI5,ARR(-32,-1008));
void SPICommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&SPImutex);
#endif
	if (!SPIArr) {
		SPIArr = ArrayAlloc(inst+1,sizeof(SPI *));
		for (i=0;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i]= SPIInit(inst);
	} else if (inst >= ArrayLength(SPIArr)) {
		i = ArrayLength(SPIArr);
		SPIArr = ArraySize(SPIArr,inst+1);
		for (;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i] = SPIInit(inst);
	} else {
		if (!SPIArr[inst]) SPIArr[inst] = SPIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&SPImutex);
#endif
	if (!SPIArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	char* arg1 = ArrayAlloc(Input32(argv[1]),sizeof(char));
	int ret = SPIArr[inst]->Read(SPIArr[inst],arg0,arg1);
	Output_32(oi,"Read",ret);
	Output_1008(oi,"Read",arg1);
	ArrayFree(arg1);
}
prototype protSPI5 = {
	NetSPI_Read,
	ArrayL(reqtypesSPI5),ArrayL(replytypesSPI5),
	SPICommand5
};

// int ReadWrite(void *me,int,const char*,char*);
// ReadWrite <int> <char*>
// ->
// <int> <char*>
ArrayAuto(int,reqtypesSPI6,ARR(-32,-1008));
ArrayAuto(int,replytypesSPI6,ARR(-32,-1008));
void SPICommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&SPImutex);
#endif
	if (!SPIArr) {
		SPIArr = ArrayAlloc(inst+1,sizeof(SPI *));
		for (i=0;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i]= SPIInit(inst);
	} else if (inst >= ArrayLength(SPIArr)) {
		i = ArrayLength(SPIArr);
		SPIArr = ArraySize(SPIArr,inst+1);
		for (;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i] = SPIInit(inst);
	} else {
		if (!SPIArr[inst]) SPIArr[inst] = SPIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&SPImutex);
#endif
	if (!SPIArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	const char* arg1 = Input_1008(argv[1]);
	char* arg2 = ArrayAlloc(Input32(argv[2]),sizeof(char));
	int ret = SPIArr[inst]->ReadWrite(SPIArr[inst],arg0,arg1,arg2);
	Output_32(oi,"ReadWrite",ret);
	Output_1008(oi,"ReadWrite",arg2);
	ArrayFree(arg2);
	ArrayFree(arg1);
}
prototype protSPI6 = {
	NetSPI_ReadWrite,
	ArrayL(reqtypesSPI6),ArrayL(replytypesSPI6),
	SPICommand6
};

// int ClockSet(void *me,uint);
// ClockSet <uint>
// ->
// <int>
ArrayAuto(int,reqtypesSPI7,ARR(32));
ArrayAuto(int,replytypesSPI7,ARR(-32));
void SPICommand7(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&SPImutex);
#endif
	if (!SPIArr) {
		SPIArr = ArrayAlloc(inst+1,sizeof(SPI *));
		for (i=0;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i]= SPIInit(inst);
	} else if (inst >= ArrayLength(SPIArr)) {
		i = ArrayLength(SPIArr);
		SPIArr = ArraySize(SPIArr,inst+1);
		for (;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i] = SPIInit(inst);
	} else {
		if (!SPIArr[inst]) SPIArr[inst] = SPIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&SPImutex);
#endif
	if (!SPIArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int ret = SPIArr[inst]->ClockSet(SPIArr[inst],arg0);
	Output_32(oi,"ClockSet",ret);
}
prototype protSPI7 = {
	NetSPI_ClockSet,
	ArrayL(reqtypesSPI7),ArrayL(replytypesSPI7),
	SPICommand7
};

// int EdgeSet(void *me,int);
// EdgeSet <int>
// ->
// <int>
ArrayAuto(int,reqtypesSPI8,ARR(-32));
ArrayAuto(int,replytypesSPI8,ARR(-32));
void SPICommand8(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&SPImutex);
#endif
	if (!SPIArr) {
		SPIArr = ArrayAlloc(inst+1,sizeof(SPI *));
		for (i=0;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i]= SPIInit(inst);
	} else if (inst >= ArrayLength(SPIArr)) {
		i = ArrayLength(SPIArr);
		SPIArr = ArraySize(SPIArr,inst+1);
		for (;i<inst;i++) SPIArr[i] = 0;
		SPIArr[i] = SPIInit(inst);
	} else {
		if (!SPIArr[inst]) SPIArr[inst] = SPIInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&SPImutex);
#endif
	if (!SPIArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = SPIArr[inst]->EdgeSet(SPIArr[inst],arg0);
	Output_32(oi,"EdgeSet",ret);
}
prototype protSPI8 = {
	NetSPI_EdgeSet,
	ArrayL(reqtypesSPI8),ArrayL(replytypesSPI8),
	SPICommand8
};

void Output1000014(OutInfo *oi,char *name,CANMessage* arg) {
	int i;
	for (i=0;i<ArrayLength(arg);i++) {
		Output1000000(oi,"flags",(arg+i)->flags);
		Output_32(oi,"id",(arg+i)->id);
		Output_1008(oi,"data",(arg+i)->data);
	}
}


CAN** CANArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t CANmutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Rx(void *me,CANMessage[1]);
// Rx
// ->
// <int> <CANMessage*>
ArrayAuto(int,reqtypesCAN1,ARR());
ArrayAuto(int,replytypesCAN1,ARR(-32,1000014));
void CANCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&CANmutex);
#endif
	if (!CANArr) {
		CANArr = ArrayAlloc(inst+1,sizeof(CAN *));
		for (i=0;i<inst;i++) CANArr[i] = 0;
		CANArr[i]= CANInit(inst);
	} else if (inst >= ArrayLength(CANArr)) {
		i = ArrayLength(CANArr);
		CANArr = ArraySize(CANArr,inst+1);
		for (;i<inst;i++) CANArr[i] = 0;
		CANArr[i] = CANInit(inst);
	} else {
		if (!CANArr[inst]) CANArr[inst] = CANInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&CANmutex);
#endif
	if (!CANArr[inst]) { Output_32(oi,"Error",-2); return; }
	CANMessage *arg0 = ArrayAlloc(1,sizeof(CANMessage));
	int ret = CANArr[inst]->Rx(CANArr[inst],arg0);
	Output_32(oi,"Rx",ret);
	Output1000014(oi,"Rx",arg0);
	ArrayFree(arg0);
}
prototype protCAN1 = {
	NetCAN_Rx,
	ArrayL(reqtypesCAN1),ArrayL(replytypesCAN1),
	CANCommand1
};

// int Tx(void *me,uint,uint,const char*);
// Tx <uint> <uint> <char*>
// ->
// <int>
ArrayAuto(int,reqtypesCAN2,ARR(32,32,-1008));
ArrayAuto(int,replytypesCAN2,ARR(-32));
void CANCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&CANmutex);
#endif
	if (!CANArr) {
		CANArr = ArrayAlloc(inst+1,sizeof(CAN *));
		for (i=0;i<inst;i++) CANArr[i] = 0;
		CANArr[i]= CANInit(inst);
	} else if (inst >= ArrayLength(CANArr)) {
		i = ArrayLength(CANArr);
		CANArr = ArraySize(CANArr,inst+1);
		for (;i<inst;i++) CANArr[i] = 0;
		CANArr[i] = CANInit(inst);
	} else {
		if (!CANArr[inst]) CANArr[inst] = CANInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&CANmutex);
#endif
	if (!CANArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	uint arg1 = Input32(argv[1]);
	const char* arg2 = Input_1008(argv[2]);
	int ret = CANArr[inst]->Tx(CANArr[inst],arg0,arg1,arg2);
	Output_32(oi,"Tx",ret);
	ArrayFree(arg2);
}
prototype protCAN2 = {
	NetCAN_Tx,
	ArrayL(reqtypesCAN2),ArrayL(replytypesCAN2),
	CANCommand2
};

// uint BaudSet(void *me,uint);
// BaudSet <uint>
// ->
// <uint>
ArrayAuto(int,reqtypesCAN3,ARR(32));
ArrayAuto(int,replytypesCAN3,ARR(32));
void CANCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&CANmutex);
#endif
	if (!CANArr) {
		CANArr = ArrayAlloc(inst+1,sizeof(CAN *));
		for (i=0;i<inst;i++) CANArr[i] = 0;
		CANArr[i]= CANInit(inst);
	} else if (inst >= ArrayLength(CANArr)) {
		i = ArrayLength(CANArr);
		CANArr = ArraySize(CANArr,inst+1);
		for (;i<inst;i++) CANArr[i] = 0;
		CANArr[i] = CANInit(inst);
	} else {
		if (!CANArr[inst]) CANArr[inst] = CANInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&CANmutex);
#endif
	if (!CANArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	uint ret = CANArr[inst]->BaudSet(CANArr[inst],arg0);
	Output32(oi,"BaudSet",ret);
}
prototype protCAN3 = {
	NetCAN_BaudSet,
	ArrayL(reqtypesCAN3),ArrayL(replytypesCAN3),
	CANCommand3
};

// uint BaudGet(void *me);
// BaudGet
// ->
// <uint>
ArrayAuto(int,reqtypesCAN4,ARR());
ArrayAuto(int,replytypesCAN4,ARR(32));
void CANCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&CANmutex);
#endif
	if (!CANArr) {
		CANArr = ArrayAlloc(inst+1,sizeof(CAN *));
		for (i=0;i<inst;i++) CANArr[i] = 0;
		CANArr[i]= CANInit(inst);
	} else if (inst >= ArrayLength(CANArr)) {
		i = ArrayLength(CANArr);
		CANArr = ArraySize(CANArr,inst+1);
		for (;i<inst;i++) CANArr[i] = 0;
		CANArr[i] = CANInit(inst);
	} else {
		if (!CANArr[inst]) CANArr[inst] = CANInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&CANmutex);
#endif
	if (!CANArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint ret = CANArr[inst]->BaudGet(CANArr[inst]);
	Output32(oi,"BaudGet",ret);
}
prototype protCAN4 = {
	NetCAN_BaudGet,
	ArrayL(reqtypesCAN4),ArrayL(replytypesCAN4),
	CANCommand4
};

// void Abort(void *me);
// Abort
// ->
//
ArrayAuto(int,reqtypesCAN5,ARR());
ArrayAuto(int,replytypesCAN5,ARR());
void CANCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&CANmutex);
#endif
	if (!CANArr) {
		CANArr = ArrayAlloc(inst+1,sizeof(CAN *));
		for (i=0;i<inst;i++) CANArr[i] = 0;
		CANArr[i]= CANInit(inst);
	} else if (inst >= ArrayLength(CANArr)) {
		i = ArrayLength(CANArr);
		CANArr = ArraySize(CANArr,inst+1);
		for (;i<inst;i++) CANArr[i] = 0;
		CANArr[i] = CANInit(inst);
	} else {
		if (!CANArr[inst]) CANArr[inst] = CANInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&CANmutex);
#endif
	if (!CANArr[inst]) { Output_32(oi,"Error",-2); return; }
	CANArr[inst]->Abort(CANArr[inst]);
}
prototype protCAN5 = {
	NetCAN_Abort,
	ArrayL(reqtypesCAN5),ArrayL(replytypesCAN5),
	CANCommand5
};

// int RxMulti(void *me,CANMessage*,int);
// RxMulti <int>
// ->
// <int> <CANMessage*>
ArrayAuto(int,reqtypesCAN6,ARR(-32));
ArrayAuto(int,replytypesCAN6,ARR(-32,1000014));
void CANCommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&CANmutex);
#endif
	if (!CANArr) {
		CANArr = ArrayAlloc(inst+1,sizeof(CAN *));
		for (i=0;i<inst;i++) CANArr[i] = 0;
		CANArr[i]= CANInit(inst);
	} else if (inst >= ArrayLength(CANArr)) {
		i = ArrayLength(CANArr);
		CANArr = ArraySize(CANArr,inst+1);
		for (;i<inst;i++) CANArr[i] = 0;
		CANArr[i] = CANInit(inst);
	} else {
		if (!CANArr[inst]) CANArr[inst] = CANInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&CANmutex);
#endif
	if (!CANArr[inst]) { Output_32(oi,"Error",-2); return; }
	CANMessage* arg0 = ArrayAlloc(Input32(argv[0]),sizeof(CANMessage));
	int arg1 = Input_32(argv[1]);
	int ret = CANArr[inst]->RxMulti(CANArr[inst],arg0,arg1);
	Output_32(oi,"RxMulti",ret);
	Output1000014(oi,"RxMulti",arg0);
	ArrayFree(arg0);
}
prototype protCAN6 = {
	NetCAN_RxMulti,
	ArrayL(reqtypesCAN6),ArrayL(replytypesCAN6),
	CANCommand6
};


AIO** AIOArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t AIOmutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Lock(void *me,uint,int);
// Lock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO1,ARR(32,-32));
ArrayAuto(int,replytypesAIO1,ARR(-32));
void AIOCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = AIOArr[inst]->Lock(AIOArr[inst],arg0,arg1);
	Output_32(oi,"Lock",ret);
}
prototype protAIO1 = {
	NetAIO_Lock,
	ArrayL(reqtypesAIO1),ArrayL(replytypesAIO1),
	AIOCommand1
};

// int Unlock(void *me,uint,int);
// Unlock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO2,ARR(32,-32));
ArrayAuto(int,replytypesAIO2,ARR(-32));
void AIOCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = AIOArr[inst]->Unlock(AIOArr[inst],arg0,arg1);
	Output_32(oi,"Unlock",ret);
}
prototype protAIO2 = {
	NetAIO_Unlock,
	ArrayL(reqtypesAIO2),ArrayL(replytypesAIO2),
	AIOCommand2
};

// int Preempt(void *me);
// Preempt
// ->
// <int>
ArrayAuto(int,reqtypesAIO3,ARR());
ArrayAuto(int,replytypesAIO3,ARR(-32));
void AIOCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = AIOArr[inst]->Preempt(AIOArr[inst]);
	Output_32(oi,"Preempt",ret);
}
prototype protAIO3 = {
	NetAIO_Preempt,
	ArrayL(reqtypesAIO3),ArrayL(replytypesAIO3),
	AIOCommand3
};

// AIOType Type(void *me);
// Type
// ->
// <AIOType>
ArrayAuto(int,reqtypesAIO4,ARR());
ArrayAuto(int,replytypesAIO4,ARR(1000001));
void AIOCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	AIOType ret = AIOArr[inst]->Type(AIOArr[inst]);
	Output1000001(oi,"Type",ret);
}
prototype protAIO4 = {
	NetAIO_Type,
	ArrayL(reqtypesAIO4),ArrayL(replytypesAIO4),
	AIOCommand4
};

// VoltageRange* VoltageRangeList(void *me);
// VoltageRangeList
// ->
// <VoltageRange*>
ArrayAuto(int,reqtypesAIO5,ARR());
ArrayAuto(int,replytypesAIO5,ARR(1000012));
void AIOCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	VoltageRange* ret = AIOArr[inst]->VoltageRangeList(AIOArr[inst]);
	Output1000012(oi,"VoltageRangeList",ret);
	ArrayFree(ret);
}
prototype protAIO5 = {
	NetAIO_VoltageRangeList,
	ArrayL(reqtypesAIO5),ArrayL(replytypesAIO5),
	AIOCommand5
};

// int PrecisionList(void *me);
// PrecisionList
// ->
// <int>
ArrayAuto(int,reqtypesAIO6,ARR());
ArrayAuto(int,replytypesAIO6,ARR(-32));
void AIOCommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = AIOArr[inst]->PrecisionList(AIOArr[inst]);
	Output_32(oi,"PrecisionList",ret);
}
prototype protAIO6 = {
	NetAIO_PrecisionList,
	ArrayL(reqtypesAIO6),ArrayL(replytypesAIO6),
	AIOCommand6
};

// PeriodRange* PeriodRangeList(void *me);
// PeriodRangeList
// ->
// <PeriodRange*>
ArrayAuto(int,reqtypesAIO7,ARR());
ArrayAuto(int,replytypesAIO7,ARR(1000013));
void AIOCommand7(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	PeriodRange* ret = AIOArr[inst]->PeriodRangeList(AIOArr[inst]);
	Output1000013(oi,"PeriodRangeList",ret);
	ArrayFree(ret);
}
prototype protAIO7 = {
	NetAIO_PeriodRangeList,
	ArrayL(reqtypesAIO7),ArrayL(replytypesAIO7),
	AIOCommand7
};

// int* TriggerList(void *me);
// TriggerList
// ->
// <int*>
ArrayAuto(int,reqtypesAIO8,ARR());
ArrayAuto(int,replytypesAIO8,ARR(-1032));
void AIOCommand8(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int* ret = AIOArr[inst]->TriggerList(AIOArr[inst]);
	Output_1032(oi,"TriggerList",ret);
	ArrayFree(ret);
}
prototype protAIO8 = {
	NetAIO_TriggerList,
	ArrayL(reqtypesAIO8),ArrayL(replytypesAIO8),
	AIOCommand8
};

// int Channels(void *me);
// Channels
// ->
// <int>
ArrayAuto(int,reqtypesAIO9,ARR());
ArrayAuto(int,replytypesAIO9,ARR(-32));
void AIOCommand9(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = AIOArr[inst]->Channels(AIOArr[inst]);
	Output_32(oi,"Channels",ret);
}
prototype protAIO9 = {
	NetAIO_Channels,
	ArrayL(reqtypesAIO9),ArrayL(replytypesAIO9),
	AIOCommand9
};

// void Reset(void *me);
// Reset
// ->
//
ArrayAuto(int,reqtypesAIO10,ARR());
ArrayAuto(int,replytypesAIO10,ARR());
void AIOCommand10(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	AIOArr[inst]->Reset(AIOArr[inst]);
}
prototype protAIO10 = {
	NetAIO_Reset,
	ArrayL(reqtypesAIO10),ArrayL(replytypesAIO10),
	AIOCommand10
};

// int ChannelEnable(void *me,int,int);
// ChannelEnable <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO11,ARR(-32,-32));
ArrayAuto(int,replytypesAIO11,ARR(-32));
void AIOCommand11(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = AIOArr[inst]->ChannelEnable(AIOArr[inst],arg0,arg1);
	Output_32(oi,"ChannelEnable",ret);
}
prototype protAIO11 = {
	NetAIO_ChannelEnable,
	ArrayL(reqtypesAIO11),ArrayL(replytypesAIO11),
	AIOCommand11
};

// uint ChannelSamplePeriod(void *me,int,uint);
// ChannelSamplePeriod <int> <uint>
// ->
// <uint>
ArrayAuto(int,reqtypesAIO12,ARR(-32,32));
ArrayAuto(int,replytypesAIO12,ARR(32));
void AIOCommand12(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uint arg1 = Input32(argv[1]);
	uint ret = AIOArr[inst]->ChannelSamplePeriod(AIOArr[inst],arg0,arg1);
	Output32(oi,"ChannelSamplePeriod",ret);
}
prototype protAIO12 = {
	NetAIO_ChannelSamplePeriod,
	ArrayL(reqtypesAIO12),ArrayL(replytypesAIO12),
	AIOCommand12
};

// int ChannelPrecision(void *me,int,int);
// ChannelPrecision <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO13,ARR(-32,-32));
ArrayAuto(int,replytypesAIO13,ARR(-32));
void AIOCommand13(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = AIOArr[inst]->ChannelPrecision(AIOArr[inst],arg0,arg1);
	Output_32(oi,"ChannelPrecision",ret);
}
prototype protAIO13 = {
	NetAIO_ChannelPrecision,
	ArrayL(reqtypesAIO13),ArrayL(replytypesAIO13),
	AIOCommand13
};

// int ChannelVoltageRange(void *me,int,float,float);
// ChannelVoltageRange <int> <float> <float>
// ->
// <int>
ArrayAuto(int,reqtypesAIO14,ARR(-32,900,900));
ArrayAuto(int,replytypesAIO14,ARR(-32));
void AIOCommand14(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	float arg1 = Input900(argv[1]);
	float arg2 = Input900(argv[2]);
	int ret = AIOArr[inst]->ChannelVoltageRange(AIOArr[inst],arg0,arg1,arg2);
	Output_32(oi,"ChannelVoltageRange",ret);
}
prototype protAIO14 = {
	NetAIO_ChannelVoltageRange,
	ArrayL(reqtypesAIO14),ArrayL(replytypesAIO14),
	AIOCommand14
};

// int Configuration(void *me,float*,float*,int*,int*,int*,int[1]);
// Configuration
// ->
// <int> <float*> <float*> <int*> <int*> <int*> <int*>
ArrayAuto(int,reqtypesAIO15,ARR());
ArrayAuto(int,replytypesAIO15,ARR(-32,1900,1900,-1032,-1032,-1032,-1032));
void AIOCommand15(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	float* arg0 = ArrayAlloc(Input32(argv[0]),sizeof(float));
	float* arg1 = ArrayAlloc(Input32(argv[1]),sizeof(float));
	int* arg2 = ArrayAlloc(Input32(argv[2]),sizeof(int));
	int* arg3 = ArrayAlloc(Input32(argv[3]),sizeof(int));
	int* arg4 = ArrayAlloc(Input32(argv[4]),sizeof(int));
	int *arg5 = ArrayAlloc(1,sizeof(int));
	int ret = AIOArr[inst]->Configuration(AIOArr[inst],arg0,arg1,arg2,arg3,arg4,arg5);
	Output_32(oi,"Configuration",ret);
	Output1900(oi,"Configuration",arg0);
	Output1900(oi,"Configuration",arg1);
	Output_1032(oi,"Configuration",arg2);
	Output_1032(oi,"Configuration",arg3);
	Output_1032(oi,"Configuration",arg4);
	Output_1032(oi,"Configuration",arg5);
	ArrayFree(arg0);
	ArrayFree(arg1);
	ArrayFree(arg2);
	ArrayFree(arg3);
	ArrayFree(arg4);
	ArrayFree(arg5);
}
prototype protAIO15 = {
	NetAIO_Configuration,
	ArrayL(reqtypesAIO15),ArrayL(replytypesAIO15),
	AIOCommand15
};

// int ConfigureTest(void *me,const float*,const float*,const int*,const int*,const int*,int);
// ConfigureTest <float*> <float*> <int*> <int*> <int*> <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO16,ARR(1900,1900,-1032,-1032,-1032,-32));
ArrayAuto(int,replytypesAIO16,ARR(-32));
void AIOCommand16(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	const float* arg0 = Input1900(argv[0]);
	const float* arg1 = Input1900(argv[1]);
	const int* arg2 = Input_1032(argv[2]);
	const int* arg3 = Input_1032(argv[3]);
	const int* arg4 = Input_1032(argv[4]);
	int arg5 = Input_32(argv[5]);
	int ret = AIOArr[inst]->ConfigureTest(AIOArr[inst],arg0,arg1,arg2,arg3,arg4,arg5);
	Output_32(oi,"ConfigureTest",ret);
	ArrayFree(arg0);
	ArrayFree(arg1);
	ArrayFree(arg2);
	ArrayFree(arg3);
	ArrayFree(arg4);
}
prototype protAIO16 = {
	NetAIO_ConfigureTest,
	ArrayL(reqtypesAIO16),ArrayL(replytypesAIO16),
	AIOCommand16
};

// int Configure(void *me,const float*,const float*,const int*,const int*,const int*,int);
// Configure <float*> <float*> <int*> <int*> <int*> <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO17,ARR(1900,1900,-1032,-1032,-1032,-32));
ArrayAuto(int,replytypesAIO17,ARR(-32));
void AIOCommand17(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	const float* arg0 = Input1900(argv[0]);
	const float* arg1 = Input1900(argv[1]);
	const int* arg2 = Input_1032(argv[2]);
	const int* arg3 = Input_1032(argv[3]);
	const int* arg4 = Input_1032(argv[4]);
	int arg5 = Input_32(argv[5]);
	int ret = AIOArr[inst]->Configure(AIOArr[inst],arg0,arg1,arg2,arg3,arg4,arg5);
	Output_32(oi,"Configure",ret);
	ArrayFree(arg0);
	ArrayFree(arg1);
	ArrayFree(arg2);
	ArrayFree(arg3);
	ArrayFree(arg4);
}
prototype protAIO17 = {
	NetAIO_Configure,
	ArrayL(reqtypesAIO17),ArrayL(replytypesAIO17),
	AIOCommand17
};

// int ITrig(void *me,int);
// ITrig <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO18,ARR(-32));
ArrayAuto(int,replytypesAIO18,ARR(-32));
void AIOCommand18(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = AIOArr[inst]->ITrig(AIOArr[inst],arg0);
	Output_32(oi,"ITrig",ret);
}
prototype protAIO18 = {
	NetAIO_ITrig,
	ArrayL(reqtypesAIO18),ArrayL(replytypesAIO18),
	AIOCommand18
};

// int Get(void *me,int);
// Get <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO19,ARR(-32));
ArrayAuto(int,replytypesAIO19,ARR(-32));
void AIOCommand19(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = AIOArr[inst]->Get(AIOArr[inst],arg0);
	Output_32(oi,"Get",ret);
}
prototype protAIO19 = {
	NetAIO_Get,
	ArrayL(reqtypesAIO19),ArrayL(replytypesAIO19),
	AIOCommand19
};

// int Put(void *me,int,int);
// Put <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO20,ARR(-32,-32));
ArrayAuto(int,replytypesAIO20,ARR(-32));
void AIOCommand20(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = AIOArr[inst]->Put(AIOArr[inst],arg0,arg1);
	Output_32(oi,"Put",ret);
}
prototype protAIO20 = {
	NetAIO_Put,
	ArrayL(reqtypesAIO20),ArrayL(replytypesAIO20),
	AIOCommand20
};

// int Ready(void *me,int);
// Ready <int>
// ->
// <int>
ArrayAuto(int,reqtypesAIO21,ARR(-32));
ArrayAuto(int,replytypesAIO21,ARR(-32));
void AIOCommand21(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = AIOArr[inst]->Ready(AIOArr[inst],arg0);
	Output_32(oi,"Ready",ret);
}
prototype protAIO21 = {
	NetAIO_Ready,
	ArrayL(reqtypesAIO21),ArrayL(replytypesAIO21),
	AIOCommand21
};

// int Gets8(void *me,char*);
// Gets8
// ->
// <int> <char*>
ArrayAuto(int,reqtypesAIO22,ARR());
ArrayAuto(int,replytypesAIO22,ARR(-32,-1008));
void AIOCommand22(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	char* arg0 = ArrayAlloc(Input32(argv[0]),sizeof(char));
	int ret = AIOArr[inst]->Gets8(AIOArr[inst],arg0);
	Output_32(oi,"Gets8",ret);
	Output_1008(oi,"Gets8",arg0);
	ArrayFree(arg0);
}
prototype protAIO22 = {
	NetAIO_Gets8,
	ArrayL(reqtypesAIO22),ArrayL(replytypesAIO22),
	AIOCommand22
};

// int Gets16(void *me,short*);
// Gets16
// ->
// <int> <short*>
ArrayAuto(int,reqtypesAIO23,ARR());
ArrayAuto(int,replytypesAIO23,ARR(-32,-1016));
void AIOCommand23(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	short* arg0 = ArrayAlloc(Input32(argv[0]),sizeof(short));
	int ret = AIOArr[inst]->Gets16(AIOArr[inst],arg0);
	Output_32(oi,"Gets16",ret);
	Output_1016(oi,"Gets16",arg0);
	ArrayFree(arg0);
}
prototype protAIO23 = {
	NetAIO_Gets16,
	ArrayL(reqtypesAIO23),ArrayL(replytypesAIO23),
	AIOCommand23
};

// int Gets32(void *me,int*);
// Gets32
// ->
// <int> <int*>
ArrayAuto(int,reqtypesAIO24,ARR());
ArrayAuto(int,replytypesAIO24,ARR(-32,-1032));
void AIOCommand24(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int* arg0 = ArrayAlloc(Input32(argv[0]),sizeof(int));
	int ret = AIOArr[inst]->Gets32(AIOArr[inst],arg0);
	Output_32(oi,"Gets32",ret);
	Output_1032(oi,"Gets32",arg0);
	ArrayFree(arg0);
}
prototype protAIO24 = {
	NetAIO_Gets32,
	ArrayL(reqtypesAIO24),ArrayL(replytypesAIO24),
	AIOCommand24
};

// int Puts8(void *me,const char*);
// Puts8 <char*>
// ->
// <int>
ArrayAuto(int,reqtypesAIO25,ARR(-1008));
ArrayAuto(int,replytypesAIO25,ARR(-32));
void AIOCommand25(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	const char* arg0 = Input_1008(argv[0]);
	int ret = AIOArr[inst]->Puts8(AIOArr[inst],arg0);
	Output_32(oi,"Puts8",ret);
	ArrayFree(arg0);
}
prototype protAIO25 = {
	NetAIO_Puts8,
	ArrayL(reqtypesAIO25),ArrayL(replytypesAIO25),
	AIOCommand25
};

// int Puts16(void *me,const short*);
// Puts16 <short*>
// ->
// <int>
ArrayAuto(int,reqtypesAIO26,ARR(-1016));
ArrayAuto(int,replytypesAIO26,ARR(-32));
void AIOCommand26(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	const short* arg0 = Input_1016(argv[0]);
	int ret = AIOArr[inst]->Puts16(AIOArr[inst],arg0);
	Output_32(oi,"Puts16",ret);
	ArrayFree(arg0);
}
prototype protAIO26 = {
	NetAIO_Puts16,
	ArrayL(reqtypesAIO26),ArrayL(replytypesAIO26),
	AIOCommand26
};

// int Puts32(void *me,const int*);
// Puts32 <int*>
// ->
// <int>
ArrayAuto(int,reqtypesAIO27,ARR(-1032));
ArrayAuto(int,replytypesAIO27,ARR(-32));
void AIOCommand27(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	const int* arg0 = Input_1032(argv[0]);
	int ret = AIOArr[inst]->Puts32(AIOArr[inst],arg0);
	Output_32(oi,"Puts32",ret);
	ArrayFree(arg0);
}
prototype protAIO27 = {
	NetAIO_Puts32,
	ArrayL(reqtypesAIO27),ArrayL(replytypesAIO27),
	AIOCommand27
};

// int Readys8(void *me,const char*);
// Readys8 <char*>
// ->
// <int>
ArrayAuto(int,reqtypesAIO28,ARR(-1008));
ArrayAuto(int,replytypesAIO28,ARR(-32));
void AIOCommand28(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	const char* arg0 = Input_1008(argv[0]);
	int ret = AIOArr[inst]->Readys8(AIOArr[inst],arg0);
	Output_32(oi,"Readys8",ret);
	ArrayFree(arg0);
}
prototype protAIO28 = {
	NetAIO_Readys8,
	ArrayL(reqtypesAIO28),ArrayL(replytypesAIO28),
	AIOCommand28
};

// int Readys16(void *me,const short*);
// Readys16 <short*>
// ->
// <int>
ArrayAuto(int,reqtypesAIO29,ARR(-1016));
ArrayAuto(int,replytypesAIO29,ARR(-32));
void AIOCommand29(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	const short* arg0 = Input_1016(argv[0]);
	int ret = AIOArr[inst]->Readys16(AIOArr[inst],arg0);
	Output_32(oi,"Readys16",ret);
	ArrayFree(arg0);
}
prototype protAIO29 = {
	NetAIO_Readys16,
	ArrayL(reqtypesAIO29),ArrayL(replytypesAIO29),
	AIOCommand29
};

// int Readys32(void *me,const int*);
// Readys32 <int*>
// ->
// <int>
ArrayAuto(int,reqtypesAIO30,ARR(-1032));
ArrayAuto(int,replytypesAIO30,ARR(-32));
void AIOCommand30(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&AIOmutex);
#endif
	if (!AIOArr) {
		AIOArr = ArrayAlloc(inst+1,sizeof(AIO *));
		for (i=0;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i]= AIOInit(inst);
	} else if (inst >= ArrayLength(AIOArr)) {
		i = ArrayLength(AIOArr);
		AIOArr = ArraySize(AIOArr,inst+1);
		for (;i<inst;i++) AIOArr[i] = 0;
		AIOArr[i] = AIOInit(inst);
	} else {
		if (!AIOArr[inst]) AIOArr[inst] = AIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&AIOmutex);
#endif
	if (!AIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	const int* arg0 = Input_1032(argv[0]);
	int ret = AIOArr[inst]->Readys32(AIOArr[inst],arg0);
	Output_32(oi,"Readys32",ret);
	ArrayFree(arg0);
}
prototype protAIO30 = {
	NetAIO_Readys32,
	ArrayL(reqtypesAIO30),ArrayL(replytypesAIO30),
	AIOCommand30
};


EDIO** EDIOArr;
#ifdef THREAD_USE_POSIX
static pthread_mutex_t EDIOmutex=PTHREAD_MUTEX_INITIALIZER;
#endif
// int Lock(void *me,uint,int);
// Lock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesEDIO1,ARR(32,-32));
ArrayAuto(int,replytypesEDIO1,ARR(-32));
void EDIOCommand1(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = EDIOArr[inst]->Lock(EDIOArr[inst],arg0,arg1);
	Output_32(oi,"Lock",ret);
}
prototype protEDIO1 = {
	NetEDIO_Lock,
	ArrayL(reqtypesEDIO1),ArrayL(replytypesEDIO1),
	EDIOCommand1
};

// int Unlock(void *me,uint,int);
// Unlock <uint> <int>
// ->
// <int>
ArrayAuto(int,reqtypesEDIO2,ARR(32,-32));
ArrayAuto(int,replytypesEDIO2,ARR(-32));
void EDIOCommand2(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	uint arg0 = Input32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = EDIOArr[inst]->Unlock(EDIOArr[inst],arg0,arg1);
	Output_32(oi,"Unlock",ret);
}
prototype protEDIO2 = {
	NetEDIO_Unlock,
	ArrayL(reqtypesEDIO2),ArrayL(replytypesEDIO2),
	EDIOCommand2
};

// int Preempt(void *me);
// Preempt
// ->
// <int>
ArrayAuto(int,reqtypesEDIO3,ARR());
ArrayAuto(int,replytypesEDIO3,ARR(-32));
void EDIOCommand3(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int ret = EDIOArr[inst]->Preempt(EDIOArr[inst]);
	Output_32(oi,"Preempt",ret);
}
prototype protEDIO3 = {
	NetEDIO_Preempt,
	ArrayL(reqtypesEDIO3),ArrayL(replytypesEDIO3),
	EDIOCommand3
};

// int* QueryFunction(void *me,int);
// QueryFunction <int>
// ->
// <int*>
ArrayAuto(int,reqtypesEDIO4,ARR(-32));
ArrayAuto(int,replytypesEDIO4,ARR(-1032));
void EDIOCommand4(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int* ret = EDIOArr[inst]->QueryFunction(EDIOArr[inst],arg0);
	Output_1032(oi,"QueryFunction",ret);
	ArrayFree(ret);
}
prototype protEDIO4 = {
	NetEDIO_QueryFunction,
	ArrayL(reqtypesEDIO4),ArrayL(replytypesEDIO4),
	EDIOCommand4
};

// int PWM(void *me,int,uint,uint);
// PWM <int> <uint> <uint>
// ->
// <int>
ArrayAuto(int,reqtypesEDIO5,ARR(-32,32,32));
ArrayAuto(int,replytypesEDIO5,ARR(-32));
void EDIOCommand5(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uint arg1 = Input32(argv[1]);
	uint arg2 = Input32(argv[2]);
	int ret = EDIOArr[inst]->PWM(EDIOArr[inst],arg0,arg1,arg2);
	Output_32(oi,"PWM",ret);
}
prototype protEDIO5 = {
	NetEDIO_PWM,
	ArrayL(reqtypesEDIO5),ArrayL(replytypesEDIO5),
	EDIOCommand5
};

// int QueryPWM(void *me,int,uint[1],uint[1]);
// QueryPWM <int>
// ->
// <int> <uint*> <uint*>
ArrayAuto(int,reqtypesEDIO6,ARR(-32));
ArrayAuto(int,replytypesEDIO6,ARR(-32,1032,1032));
void EDIOCommand6(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uint *arg1 = ArrayAlloc(1,sizeof(uint));
	uint *arg2 = ArrayAlloc(1,sizeof(uint));
	int ret = EDIOArr[inst]->QueryPWM(EDIOArr[inst],arg0,arg1,arg2);
	Output_32(oi,"QueryPWM",ret);
	Output1032(oi,"QueryPWM",arg1);
	Output1032(oi,"QueryPWM",arg2);
	ArrayFree(arg1);
	ArrayFree(arg2);
}
prototype protEDIO6 = {
	NetEDIO_QueryPWM,
	ArrayL(reqtypesEDIO6),ArrayL(replytypesEDIO6),
	EDIOCommand6
};

// int PWMfd(void *me,int,uint,uint);
// PWMfd <int> <uint> <uint>
// ->
// <int>
ArrayAuto(int,reqtypesEDIO7,ARR(-32,32,32));
ArrayAuto(int,replytypesEDIO7,ARR(-32));
void EDIOCommand7(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uint arg1 = Input32(argv[1]);
	uint arg2 = Input32(argv[2]);
	int ret = EDIOArr[inst]->PWMfd(EDIOArr[inst],arg0,arg1,arg2);
	Output_32(oi,"PWMfd",ret);
}
prototype protEDIO7 = {
	NetEDIO_PWMfd,
	ArrayL(reqtypesEDIO7),ArrayL(replytypesEDIO7),
	EDIOCommand7
};

// int QueryPWMfd(void *me,int,uint[1],uint[1]);
// QueryPWMfd <int>
// ->
// <int> <uint*> <uint*>
ArrayAuto(int,reqtypesEDIO8,ARR(-32));
ArrayAuto(int,replytypesEDIO8,ARR(-32,1032,1032));
void EDIOCommand8(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	uint *arg1 = ArrayAlloc(1,sizeof(uint));
	uint *arg2 = ArrayAlloc(1,sizeof(uint));
	int ret = EDIOArr[inst]->QueryPWMfd(EDIOArr[inst],arg0,arg1,arg2);
	Output_32(oi,"QueryPWMfd",ret);
	Output1032(oi,"QueryPWMfd",arg1);
	Output1032(oi,"QueryPWMfd",arg2);
	ArrayFree(arg1);
	ArrayFree(arg2);
}
prototype protEDIO8 = {
	NetEDIO_QueryPWMfd,
	ArrayL(reqtypesEDIO8),ArrayL(replytypesEDIO8),
	EDIOCommand8
};

// int QuadratureCount(void *me,int);
// QuadratureCount <int>
// ->
// <int>
ArrayAuto(int,reqtypesEDIO9,ARR(-32));
ArrayAuto(int,replytypesEDIO9,ARR(-32));
void EDIOCommand9(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = EDIOArr[inst]->QuadratureCount(EDIOArr[inst],arg0);
	Output_32(oi,"QuadratureCount",ret);
}
prototype protEDIO9 = {
	NetEDIO_QuadratureCount,
	ArrayL(reqtypesEDIO9),ArrayL(replytypesEDIO9),
	EDIOCommand9
};

// uint64 EdgeCount(void *me,int,int);
// EdgeCount <int> <int>
// ->
// <uint64>
ArrayAuto(int,reqtypesEDIO10,ARR(-32,-32));
ArrayAuto(int,replytypesEDIO10,ARR(64));
void EDIOCommand10(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	uint64 ret = EDIOArr[inst]->EdgeCount(EDIOArr[inst],arg0,arg1);
	Output64(oi,"EdgeCount",ret);
}
prototype protEDIO10 = {
	NetEDIO_EdgeCount,
	ArrayL(reqtypesEDIO10),ArrayL(replytypesEDIO10),
	EDIOCommand10
};

// int Glitched(void *me,int);
// Glitched <int>
// ->
// <int>
ArrayAuto(int,reqtypesEDIO11,ARR(-32));
ArrayAuto(int,replytypesEDIO11,ARR(-32));
void EDIOCommand11(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int ret = EDIOArr[inst]->Glitched(EDIOArr[inst],arg0);
	Output_32(oi,"Glitched",ret);
}
prototype protEDIO11 = {
	NetEDIO_Glitched,
	ArrayL(reqtypesEDIO11),ArrayL(replytypesEDIO11),
	EDIOCommand11
};

// int HBridge(void *me,int,int);
// HBridge <int> <int>
// ->
// <int>
ArrayAuto(int,reqtypesEDIO12,ARR(-32,-32));
ArrayAuto(int,replytypesEDIO12,ARR(-32));
void EDIOCommand12(OutInfo *oi,int inst,char *argv[]) {
	int i;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&EDIOmutex);
#endif
	if (!EDIOArr) {
		EDIOArr = ArrayAlloc(inst+1,sizeof(EDIO *));
		for (i=0;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i]= EDIOInit(inst);
	} else if (inst >= ArrayLength(EDIOArr)) {
		i = ArrayLength(EDIOArr);
		EDIOArr = ArraySize(EDIOArr,inst+1);
		for (;i<inst;i++) EDIOArr[i] = 0;
		EDIOArr[i] = EDIOInit(inst);
	} else {
		if (!EDIOArr[inst]) EDIOArr[inst] = EDIOInit(inst);
	}
#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&EDIOmutex);
#endif
	if (!EDIOArr[inst]) { Output_32(oi,"Error",-2); return; }
	int arg0 = Input_32(argv[0]);
	int arg1 = Input_32(argv[1]);
	int ret = EDIOArr[inst]->HBridge(EDIOArr[inst],arg0,arg1);
	Output_32(oi,"HBridge",ret);
}
prototype protEDIO12 = {
	NetEDIO_HBridge,
	ArrayL(reqtypesEDIO12),ArrayL(replytypesEDIO12),
	EDIOCommand12
};


#ifdef THREAD_USE_POSIX
static pthread_mutex_t protomutex=PTHREAD_MUTEX_INITIALIZER;
#endif

HashTable *ci;

void PrototypeInit() {
	static int initialized=0;

#ifdef THREAD_USE_POSIX
	pthread_mutex_lock(&protomutex);
#endif
	if (initialized) goto PrototypeInitDone;
	initialized = 1;
	ci = HashTableNewASCIIZ();	
	HashTableInsert(ci,"System ClassCount",(char*)&protSystem1);
	HashTableInsert(ci,"System InstanceCount",(char*)&protSystem2);
	HashTableInsert(ci,"System APICount",(char*)&protSystem3);
	HashTableInsert(ci,"System LockCount",(char*)&protSystem4);
	HashTableInsert(ci,"System LockHolderInfo",(char*)&protSystem5);
	HashTableInsert(ci,"System ConnWaitInfo",(char*)&protSystem6);
	HashTableInsert(ci,"System CANBusGet",(char*)&protSystem7);
	HashTableInsert(ci,"System BuildInfo",(char*)&protSystem8);
	HashTableInsert(ci,"System ModelId",(char*)&protSystem9);
	HashTableInsert(ci,"System BaseBoardId",(char*)&protSystem10);
	HashTableInsert(ci,"System MapLength",(char*)&protSystem11);
	HashTableInsert(ci,"System MapGet",(char*)&protSystem12);
	HashTableInsert(ci,"System MapLookup",(char*)&protSystem13);
	HashTableInsert(ci,"System MapLookupPartial",(char*)&protSystem14);
	HashTableInsert(ci,"System MapAdd",(char*)&protSystem15);
	HashTableInsert(ci,"System MapDelete",(char*)&protSystem16);
	HashTableInsert(ci,"Bus Lock",(char*)&protBus1);
	HashTableInsert(ci,"Bus Unlock",(char*)&protBus2);
	HashTableInsert(ci,"Bus Preempt",(char*)&protBus3);
	HashTableInsert(ci,"Bus Peek8",(char*)&protBus4);
	HashTableInsert(ci,"Bus Poke8",(char*)&protBus5);
	HashTableInsert(ci,"Bus Peek16",(char*)&protBus6);
	HashTableInsert(ci,"Bus Poke16",(char*)&protBus7);
	HashTableInsert(ci,"Bus Peek32",(char*)&protBus8);
	HashTableInsert(ci,"Bus Poke32",(char*)&protBus9);
	HashTableInsert(ci,"Bus BitGet8",(char*)&protBus10);
	HashTableInsert(ci,"Bus BitAssign8",(char*)&protBus11);
	HashTableInsert(ci,"Bus BitSet8",(char*)&protBus12);
	HashTableInsert(ci,"Bus BitClear8",(char*)&protBus13);
	HashTableInsert(ci,"Bus BitGet16",(char*)&protBus14);
	HashTableInsert(ci,"Bus BitAssign16",(char*)&protBus15);
	HashTableInsert(ci,"Bus BitSet16",(char*)&protBus16);
	HashTableInsert(ci,"Bus BitClear16",(char*)&protBus17);
	HashTableInsert(ci,"Bus BitGet32",(char*)&protBus18);
	HashTableInsert(ci,"Bus BitAssign32",(char*)&protBus19);
	HashTableInsert(ci,"Bus BitSet32",(char*)&protBus20);
	HashTableInsert(ci,"Bus BitClear32",(char*)&protBus21);
	HashTableInsert(ci,"Bus PeekStream",(char*)&protBus22);
	HashTableInsert(ci,"Bus PokeStream",(char*)&protBus23);
	HashTableInsert(ci,"Bus Refresh",(char*)&protBus24);
	HashTableInsert(ci,"Bus Commit",(char*)&protBus25);
	HashTableInsert(ci,"Bus BitToggle8",(char*)&protBus26);
	HashTableInsert(ci,"Bus BitToggle16",(char*)&protBus27);
	HashTableInsert(ci,"Bus BitToggle32",(char*)&protBus28);
	HashTableInsert(ci,"Bus Assign8X",(char*)&protBus29);
	HashTableInsert(ci,"Bus Assign16X",(char*)&protBus30);
	HashTableInsert(ci,"Bus Assign32X",(char*)&protBus31);
	HashTableInsert(ci,"Bus BitsGet8",(char*)&protBus32);
	HashTableInsert(ci,"Bus BitsGet16",(char*)&protBus33);
	HashTableInsert(ci,"Bus BitsGet32",(char*)&protBus34);
	HashTableInsert(ci,"Time Wait",(char*)&protTime1);
	HashTableInsert(ci,"Time Delay",(char*)&protTime2);
	HashTableInsert(ci,"Time Tick",(char*)&protTime3);
	HashTableInsert(ci,"Time usElapsed",(char*)&protTime4);
	HashTableInsert(ci,"Time usFuture",(char*)&protTime5);
	HashTableInsert(ci,"Time TimeoutQ",(char*)&protTime6);
	HashTableInsert(ci,"Time TPS",(char*)&protTime7);
	HashTableInsert(ci,"Pin Lock",(char*)&protPin1);
	HashTableInsert(ci,"Pin Unlock",(char*)&protPin2);
	HashTableInsert(ci,"Pin Preempt",(char*)&protPin3);
	HashTableInsert(ci,"Pin ModeGet",(char*)&protPin4);
	HashTableInsert(ci,"Pin ModeSet",(char*)&protPin5);
	HashTableInsert(ci,"DIORaw Lock",(char*)&protDIORaw1);
	HashTableInsert(ci,"DIORaw Unlock",(char*)&protDIORaw2);
	HashTableInsert(ci,"DIORaw Preempt",(char*)&protDIORaw3);
	HashTableInsert(ci,"DIORaw DirSet",(char*)&protDIORaw4);
	HashTableInsert(ci,"DIORaw DataSet",(char*)&protDIORaw5);
	HashTableInsert(ci,"DIORaw DirGet",(char*)&protDIORaw6);
	HashTableInsert(ci,"DIORaw DataGet",(char*)&protDIORaw7);
	HashTableInsert(ci,"DIORaw Count",(char*)&protDIORaw8);
	HashTableInsert(ci,"DIO Lock",(char*)&protDIO1);
	HashTableInsert(ci,"DIO Unlock",(char*)&protDIO2);
	HashTableInsert(ci,"DIO Preempt",(char*)&protDIO3);
	HashTableInsert(ci,"DIO Refresh",(char*)&protDIO4);
	HashTableInsert(ci,"DIO Commit",(char*)&protDIO5);
	HashTableInsert(ci,"DIO Set",(char*)&protDIO6);
	HashTableInsert(ci,"DIO Get",(char*)&protDIO7);
	HashTableInsert(ci,"DIO SetAsync",(char*)&protDIO8);
	HashTableInsert(ci,"DIO GetAsync",(char*)&protDIO9);
	HashTableInsert(ci,"DIO Wait",(char*)&protDIO10);
	HashTableInsert(ci,"DIO Count",(char*)&protDIO11);
	HashTableInsert(ci,"DIO Capabilities",(char*)&protDIO12);
	HashTableInsert(ci,"DIO GetMulti",(char*)&protDIO13);
	HashTableInsert(ci,"TWI Lock",(char*)&protTWI1);
	HashTableInsert(ci,"TWI Unlock",(char*)&protTWI2);
	HashTableInsert(ci,"TWI Preempt",(char*)&protTWI3);
	HashTableInsert(ci,"TWI Write",(char*)&protTWI4);
	HashTableInsert(ci,"TWI Read",(char*)&protTWI5);
	HashTableInsert(ci,"SPI Lock",(char*)&protSPI1);
	HashTableInsert(ci,"SPI Unlock",(char*)&protSPI2);
	HashTableInsert(ci,"SPI Preempt",(char*)&protSPI3);
	HashTableInsert(ci,"SPI Write",(char*)&protSPI4);
	HashTableInsert(ci,"SPI Read",(char*)&protSPI5);
	HashTableInsert(ci,"SPI ReadWrite",(char*)&protSPI6);
	HashTableInsert(ci,"SPI ClockSet",(char*)&protSPI7);
	HashTableInsert(ci,"SPI EdgeSet",(char*)&protSPI8);
	HashTableInsert(ci,"CAN Rx",(char*)&protCAN1);
	HashTableInsert(ci,"CAN Tx",(char*)&protCAN2);
	HashTableInsert(ci,"CAN BaudSet",(char*)&protCAN3);
	HashTableInsert(ci,"CAN BaudGet",(char*)&protCAN4);
	HashTableInsert(ci,"CAN Abort",(char*)&protCAN5);
	HashTableInsert(ci,"CAN RxMulti",(char*)&protCAN6);
	HashTableInsert(ci,"AIO Lock",(char*)&protAIO1);
	HashTableInsert(ci,"AIO Unlock",(char*)&protAIO2);
	HashTableInsert(ci,"AIO Preempt",(char*)&protAIO3);
	HashTableInsert(ci,"AIO Type",(char*)&protAIO4);
	HashTableInsert(ci,"AIO VoltageRangeList",(char*)&protAIO5);
	HashTableInsert(ci,"AIO PrecisionList",(char*)&protAIO6);
	HashTableInsert(ci,"AIO PeriodRangeList",(char*)&protAIO7);
	HashTableInsert(ci,"AIO TriggerList",(char*)&protAIO8);
	HashTableInsert(ci,"AIO Channels",(char*)&protAIO9);
	HashTableInsert(ci,"AIO Reset",(char*)&protAIO10);
	HashTableInsert(ci,"AIO ChannelEnable",(char*)&protAIO11);
	HashTableInsert(ci,"AIO ChannelSamplePeriod",(char*)&protAIO12);
	HashTableInsert(ci,"AIO ChannelPrecision",(char*)&protAIO13);
	HashTableInsert(ci,"AIO ChannelVoltageRange",(char*)&protAIO14);
	HashTableInsert(ci,"AIO Configuration",(char*)&protAIO15);
	HashTableInsert(ci,"AIO ConfigureTest",(char*)&protAIO16);
	HashTableInsert(ci,"AIO Configure",(char*)&protAIO17);
	HashTableInsert(ci,"AIO ITrig",(char*)&protAIO18);
	HashTableInsert(ci,"AIO Get",(char*)&protAIO19);
	HashTableInsert(ci,"AIO Put",(char*)&protAIO20);
	HashTableInsert(ci,"AIO Ready",(char*)&protAIO21);
	HashTableInsert(ci,"AIO Gets8",(char*)&protAIO22);
	HashTableInsert(ci,"AIO Gets16",(char*)&protAIO23);
	HashTableInsert(ci,"AIO Gets32",(char*)&protAIO24);
	HashTableInsert(ci,"AIO Puts8",(char*)&protAIO25);
	HashTableInsert(ci,"AIO Puts16",(char*)&protAIO26);
	HashTableInsert(ci,"AIO Puts32",(char*)&protAIO27);
	HashTableInsert(ci,"AIO Readys8",(char*)&protAIO28);
	HashTableInsert(ci,"AIO Readys16",(char*)&protAIO29);
	HashTableInsert(ci,"AIO Readys32",(char*)&protAIO30);
	HashTableInsert(ci,"EDIO Lock",(char*)&protEDIO1);
	HashTableInsert(ci,"EDIO Unlock",(char*)&protEDIO2);
	HashTableInsert(ci,"EDIO Preempt",(char*)&protEDIO3);
	HashTableInsert(ci,"EDIO QueryFunction",(char*)&protEDIO4);
	HashTableInsert(ci,"EDIO PWM",(char*)&protEDIO5);
	HashTableInsert(ci,"EDIO QueryPWM",(char*)&protEDIO6);
	HashTableInsert(ci,"EDIO PWMfd",(char*)&protEDIO7);
	HashTableInsert(ci,"EDIO QueryPWMfd",(char*)&protEDIO8);
	HashTableInsert(ci,"EDIO QuadratureCount",(char*)&protEDIO9);
	HashTableInsert(ci,"EDIO EdgeCount",(char*)&protEDIO10);
	HashTableInsert(ci,"EDIO Glitched",(char*)&protEDIO11);
	HashTableInsert(ci,"EDIO HBridge",(char*)&protEDIO12);
	SystemArr = ArrayAlloc(1,sizeof(System *));
	SystemArr[0]= SystemInit(0);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_DIOCTL"),0x400000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_RETURN"),0x8000000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_DEPTH"),0x4000000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_TIMESTAMP"),0x800000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_FUNCTION"),0x40000000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_PIN"),0x8);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_SYSTEM"),0x1);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_CAN"),0x80);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_FILELINE"),0x80000000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_TIME"),0x4);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_SPI"),0x100);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_THREADID"),0x20000000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_BUS"),0x2);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_ENTER"),0x10000000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_ASSERT"),0x100000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_TWI"),0x40);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_DIORAW"),0x10);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_THREAD"),0x200000);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOG_DIO"),0x20);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.EDIO_EDGECOUNT"),0x3);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.EDIO_PWM"),0x1);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.EDIO_GLITCHED"),0x4);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.EDIO_QUADRATURE"),0x2);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassSystem"),0x0);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassEDIO"),0xA);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassPin"),0x3);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassSPI"),0x8);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassBus"),0x1);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassAIO"),0xB);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassTWI"),0x6);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassDIORaw"),0x4);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassDIO"),0x5);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassTime"),0x2);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.ClassCAN"),0x7);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_DIO"),0x0);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_ADC"),0x3);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_UNKNOWN"),0xFFFFFFFF);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_PWM"),0x8);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_CAN"),0x1);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_TS"),0x6);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_TWI"),0x4);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_UART"),0x5);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_SPI"),0x2);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.MODE_BUS"),0x7);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.AIO_ADC"),0x1);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.AIO_DAC"),0x2);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.RTR"),0x10);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.EXT"),0x20);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.LOW"),0x0);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.INPUT"),0xFFFFFFFF);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.HIGH"),0x1);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.INPUT_HIGH"),0xFFFFFFFE);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.INPUT_LOW"),0xFFFFFFFD);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.DIO_NOT_PRESENT"),0x0);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.DIO_INPUT_ONLY"),0x1);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.DIO_OUTPUT_ONLY"),0x6);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.DIO_CAN_DRIVE_LOW"),0x4);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.DIO_CAN_DRIVE_HIGH"),0x2);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.DIO_NORMAL"),0x7);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.HB_FREE_RUNNING"),0x3);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.HB_LEFT"),0x1);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.HB_BRAKING"),0x4);
	SystemArr[0]->MapAdd(SystemArr[0],ASCIIZ("enum.HB_RIGHT"),0x2);
PrototypeInitDone:

#ifdef THREAD_USE_POSIX
	pthread_mutex_unlock(&protomutex);
#endif
}
