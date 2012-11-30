int tsctlClassTextToBin(char *str) {
  switch (*str++) {
  case 'A':case 'a': return 9;
  case 'B':case 'b': return 1;
  case 'C':case 'c': return 7;
  case 'D':case 'd':
    switch (*str++) {
    case 'I':case 'i':
      switch (*str++) {
      case 'O':case 'o':
        switch (*str++) {
        case 0: return 5;
        case 'R':case 'r': return 4;
        }
        break;
      }
      break;
    }
    break;
  case 'E':case 'e': return 10;
  case 'M':case 'm': return 11;
  case 'P':case 'p': return 3;
  case 'S':case 's':
    switch (*str++) {
    case 'P':case 'p': return 8;
    case 'Y':case 'y': return 0;
    }
    break;
  case 'T':case 't':
    switch (*str++) {
    case 'I':case 'i': return 2;
    case 'W':case 'w': return 6;
    }
    break;
  }
  return -1;
}
int tsctlSystemCommandTextToBin(char *str) {
  switch (*str++) {
  case 'A':case 'a': return 4;
  case 'B':case 'b':
    switch (*str++) {
    case 'A':case 'a': return 11;
    case 'U':case 'u': return 9;
    }
    break;
  case 'C':case 'c':
    switch (*str++) {
    case 'A':case 'a': return 8;
    case 'L':case 'l': return 2;
    case 'O':case 'o': return 7;
    }
    break;
  case 'F':case 'f': return 1;
  case 'I':case 'i':
    switch (*str++) {
    case 'N':case 'n':
      switch (*str++) {
      case 'I':case 'i': return 0;
      case 'S':case 's': return 3;
      }
      break;
    }
    break;
  case 'L':case 'l':
    switch (*str++) {
    case 'O':case 'o':
      switch (*str++) {
      case 'C':case 'c':
        switch (*str++) {
        case 'K':case 'k':
          switch (*str++) {
          case 'C':case 'c': return 5;
          case 'H':case 'h': return 6;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'M':case 'm':
    switch (*str++) {
    case 'A':case 'a':
      switch (*str++) {
      case 'P':case 'p':
        switch (*str++) {
        case 'A':case 'a': return 16;
        case 'D':case 'd': return 17;
        case 'G':case 'g': return 13;
        case 'L':case 'l':
          switch (*str++) {
          case 'E':case 'e': return 12;
          case 'O':case 'o':
            switch (*str++) {
            case 'O':case 'o':
              switch (*str++) {
              case 'K':case 'k':
                switch (*str++) {
                case 'U':case 'u':
                  switch (*str++) {
                  case 'P':case 'p':
                    switch (*str++) {
                    case 0: return 14;
                    case 'P':case 'p': return 15;
                    }
                    break;
                  }
                  break;
                }
                break;
              }
              break;
            }
            break;
          }
          break;
        }
        break;
      }
      break;
    case 'O':case 'o': return 10;
    }
    break;
  case 'N':case 'n': return 18;
  }
  return -1;
}
int tsctlBusCommandTextToBin(char *str) {
  switch (*str++) {
  case 'A':case 'a':
    switch (*str++) {
    case 'S':case 's':
      switch (*str++) {
      case 'S':case 's':
        switch (*str++) {
        case 'I':case 'i':
          switch (*str++) {
          case 'G':case 'g':
            switch (*str++) {
            case 'N':case 'n':
              switch (*str++) {
              case '1': return 31;
              case '3': return 32;
              case '8': return 30;
              }
              break;
            }
            break;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'B':case 'b':
    switch (*str++) {
    case 'I':case 'i':
      switch (*str++) {
      case 'T':case 't':
        switch (*str++) {
        case 'A':case 'a':
          switch (*str++) {
          case 'S':case 's':
            switch (*str++) {
            case 'S':case 's':
              switch (*str++) {
              case 'I':case 'i':
                switch (*str++) {
                case 'G':case 'g':
                  switch (*str++) {
                  case 'N':case 'n':
                    switch (*str++) {
                    case '1': return 16;
                    case '3': return 20;
                    case '8': return 12;
                    }
                    break;
                  }
                  break;
                }
                break;
              }
              break;
            }
            break;
          }
          break;
        case 'C':case 'c':
          switch (*str++) {
          case 'L':case 'l':
            switch (*str++) {
            case 'E':case 'e':
              switch (*str++) {
              case 'A':case 'a':
                switch (*str++) {
                case 'R':case 'r':
                  switch (*str++) {
                  case '1': return 18;
                  case '3': return 22;
                  case '8': return 14;
                  }
                  break;
                }
                break;
              }
              break;
            }
            break;
          }
          break;
        case 'G':case 'g':
          switch (*str++) {
          case 'E':case 'e':
            switch (*str++) {
            case 'T':case 't':
              switch (*str++) {
              case '1': return 15;
              case '3': return 19;
              case '8': return 11;
              }
              break;
            }
            break;
          }
          break;
        case 'S':case 's':
          switch (*str++) {
          case 'E':case 'e':
            switch (*str++) {
            case 'T':case 't':
              switch (*str++) {
              case '1': return 17;
              case '3': return 21;
              case '8': return 13;
              }
              break;
            }
            break;
          case 'G':case 'g':
            switch (*str++) {
            case 'E':case 'e':
              switch (*str++) {
              case 'T':case 't':
                switch (*str++) {
                case '1': return 34;
                case '3': return 35;
                case '8': return 33;
                }
                break;
              }
              break;
            }
            break;
          }
          break;
        case 'T':case 't':
          switch (*str++) {
          case 'O':case 'o':
            switch (*str++) {
            case 'G':case 'g':
              switch (*str++) {
              case 'G':case 'g':
                switch (*str++) {
                case 'L':case 'l':
                  switch (*str++) {
                  case 'E':case 'e':
                    switch (*str++) {
                    case '1': return 28;
                    case '3': return 29;
                    case '8': return 27;
                    }
                    break;
                  }
                  break;
                }
                break;
              }
              break;
            }
            break;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'C':case 'c': return 26;
  case 'F':case 'f': return 1;
  case 'I':case 'i': return 0;
  case 'L':case 'l': return 2;
  case 'P':case 'p':
    switch (*str++) {
    case 'E':case 'e':
      switch (*str++) {
      case 'E':case 'e':
        switch (*str++) {
        case 'K':case 'k':
          switch (*str++) {
          case '1': return 7;
          case '3': return 9;
          case '8': return 5;
          case 'S':case 's': return 23;
          }
          break;
        }
        break;
      }
      break;
    case 'O':case 'o':
      switch (*str++) {
      case 'K':case 'k':
        switch (*str++) {
        case 'E':case 'e':
          switch (*str++) {
          case '1': return 8;
          case '3': return 10;
          case '8': return 6;
          case 'S':case 's': return 24;
          }
          break;
        }
        break;
      }
      break;
    case 'R':case 'r': return 4;
    }
    break;
  case 'R':case 'r': return 25;
  case 'U':case 'u': return 3;
  }
  return -1;
}
int tsctlTimeCommandTextToBin(char *str) {
  switch (*str++) {
  case 'D':case 'd': return 3;
  case 'F':case 'f': return 1;
  case 'I':case 'i': return 0;
  case 'T':case 't':
    switch (*str++) {
    case 'I':case 'i':
      switch (*str++) {
      case 'C':case 'c': return 4;
      case 'M':case 'm': return 7;
      }
      break;
    case 'P':case 'p': return 8;
    }
    break;
  case 'U':case 'u':
    switch (*str++) {
    case 'S':case 's':
      switch (*str++) {
      case 'E':case 'e': return 5;
      case 'F':case 'f': return 6;
      }
      break;
    }
    break;
  case 'W':case 'w': return 2;
  }
  return -1;
}
int tsctlPinCommandTextToBin(char *str) {
  switch (*str++) {
  case 'F':case 'f': return 1;
  case 'I':case 'i': return 0;
  case 'L':case 'l': return 2;
  case 'M':case 'm':
    switch (*str++) {
    case 'O':case 'o':
      switch (*str++) {
      case 'D':case 'd':
        switch (*str++) {
        case 'E':case 'e':
          switch (*str++) {
          case 'G':case 'g': return 5;
          case 'S':case 's': return 6;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'P':case 'p': return 4;
  case 'U':case 'u': return 3;
  }
  return -1;
}
int tsctlDIORawCommandTextToBin(char *str) {
  switch (*str++) {
  case 'C':case 'c': return 9;
  case 'D':case 'd':
    switch (*str++) {
    case 'A':case 'a':
      switch (*str++) {
      case 'T':case 't':
        switch (*str++) {
        case 'A':case 'a':
          switch (*str++) {
          case 'G':case 'g': return 8;
          case 'S':case 's': return 6;
          }
          break;
        }
        break;
      }
      break;
    case 'I':case 'i':
      switch (*str++) {
      case 'R':case 'r':
        switch (*str++) {
        case 'G':case 'g': return 7;
        case 'S':case 's': return 5;
        }
        break;
      }
      break;
    }
    break;
  case 'F':case 'f': return 1;
  case 'I':case 'i': return 0;
  case 'L':case 'l': return 2;
  case 'P':case 'p': return 4;
  case 'U':case 'u': return 3;
  }
  return -1;
}
int tsctlDIOCommandTextToBin(char *str) {
  switch (*str++) {
  case 'C':case 'c':
    switch (*str++) {
    case 'A':case 'a': return 13;
    case 'O':case 'o':
      switch (*str++) {
      case 'M':case 'm': return 6;
      case 'U':case 'u': return 12;
      }
      break;
    }
    break;
  case 'F':case 'f': return 1;
  case 'G':case 'g':
    switch (*str++) {
    case 'E':case 'e':
      switch (*str++) {
      case 'T':case 't':
        switch (*str++) {
        case 0: return 8;
        case 'A':case 'a': return 10;
        case 'M':case 'm': return 14;
        }
        break;
      }
      break;
    }
    break;
  case 'I':case 'i': return 0;
  case 'L':case 'l': return 2;
  case 'P':case 'p': return 4;
  case 'R':case 'r': return 5;
  case 'S':case 's':
    switch (*str++) {
    case 'E':case 'e':
      switch (*str++) {
      case 'T':case 't':
        switch (*str++) {
        case 0: return 7;
        case 'A':case 'a': return 9;
        }
        break;
      }
      break;
    }
    break;
  case 'U':case 'u': return 3;
  case 'W':case 'w': return 11;
  }
  return -1;
}
int tsctlTWICommandTextToBin(char *str) {
  switch (*str++) {
  case 'F':case 'f': return 1;
  case 'I':case 'i': return 0;
  case 'L':case 'l': return 2;
  case 'P':case 'p': return 4;
  case 'R':case 'r': return 6;
  case 'U':case 'u': return 3;
  case 'W':case 'w': return 5;
  }
  return -1;
}
int tsctlCANCommandTextToBin(char *str) {
  switch (*str++) {
  case 'A':case 'a': return 6;
  case 'B':case 'b':
    switch (*str++) {
    case 'A':case 'a':
      switch (*str++) {
      case 'U':case 'u':
        switch (*str++) {
        case 'D':case 'd':
          switch (*str++) {
          case 'G':case 'g': return 5;
          case 'S':case 's': return 4;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'F':case 'f': return 1;
  case 'I':case 'i': return 0;
  case 'R':case 'r':
    switch (*str++) {
    case 'X':case 'x':
      switch (*str++) {
      case 0: return 2;
      case 'M':case 'm': return 7;
      }
      break;
    }
    break;
  case 'T':case 't': return 3;
  }
  return -1;
}
int tsctlSPICommandTextToBin(char *str) {
  switch (*str++) {
  case 'C':case 'c': return 8;
  case 'E':case 'e': return 9;
  case 'F':case 'f': return 1;
  case 'I':case 'i': return 0;
  case 'L':case 'l': return 2;
  case 'P':case 'p': return 4;
  case 'R':case 'r':
    switch (*str++) {
    case 'E':case 'e':
      switch (*str++) {
      case 'A':case 'a':
        switch (*str++) {
        case 'D':case 'd':
          switch (*str++) {
          case 0: return 6;
          case 'W':case 'w': return 7;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'U':case 'u': return 3;
  case 'W':case 'w': return 5;
  }
  return -1;
}
int tsctlAIOCommandTextToBin(char *str) {
  switch (*str++) {
  case 'C':case 'c':
    switch (*str++) {
    case 'H':case 'h':
      switch (*str++) {
      case 'A':case 'a':
        switch (*str++) {
        case 'N':case 'n':
          switch (*str++) {
          case 'N':case 'n':
            switch (*str++) {
            case 'E':case 'e':
              switch (*str++) {
              case 'L':case 'l':
                switch (*str++) {
                case 'E':case 'e': return 12;
                case 'P':case 'p': return 14;
                case 'S':case 's':
                  switch (*str++) {
                  case 0: return 10;
                  case 'A':case 'a': return 13;
                  }
                  break;
                case 'V':case 'v': return 15;
                }
                break;
              }
              break;
            }
            break;
          }
          break;
        }
        break;
      }
      break;
    case 'O':case 'o':
      switch (*str++) {
      case 'N':case 'n':
        switch (*str++) {
        case 'F':case 'f':
          switch (*str++) {
          case 'I':case 'i':
            switch (*str++) {
            case 'G':case 'g':
              switch (*str++) {
              case 'U':case 'u':
                switch (*str++) {
                case 'R':case 'r':
                  switch (*str++) {
                  case 'A':case 'a': return 16;
                  case 'E':case 'e':
                    switch (*str++) {
                    case 0: return 18;
                    case 'T':case 't': return 17;
                    }
                    break;
                  }
                  break;
                }
                break;
              }
              break;
            }
            break;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'F':case 'f': return 1;
  case 'G':case 'g':
    switch (*str++) {
    case 'E':case 'e':
      switch (*str++) {
      case 'T':case 't':
        switch (*str++) {
        case 0: return 20;
        case 'S':case 's':
          switch (*str++) {
          case '1': return 24;
          case '3': return 25;
          case '8': return 23;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'I':case 'i':
    switch (*str++) {
    case 'N':case 'n': return 0;
    case 'T':case 't': return 19;
    }
    break;
  case 'L':case 'l': return 2;
  case 'P':case 'p':
    switch (*str++) {
    case 'E':case 'e': return 8;
    case 'R':case 'r':
      switch (*str++) {
      case 'E':case 'e':
        switch (*str++) {
        case 'C':case 'c': return 7;
        case 'E':case 'e': return 4;
        }
        break;
      }
      break;
    case 'U':case 'u':
      switch (*str++) {
      case 'T':case 't':
        switch (*str++) {
        case 0: return 21;
        case 'S':case 's':
          switch (*str++) {
          case '1': return 27;
          case '3': return 28;
          case '8': return 26;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'R':case 'r':
    switch (*str++) {
    case 'E':case 'e':
      switch (*str++) {
      case 'A':case 'a':
        switch (*str++) {
        case 'D':case 'd':
          switch (*str++) {
          case 'Y':case 'y':
            switch (*str++) {
            case 0: return 22;
            case 'S':case 's':
              switch (*str++) {
              case '1': return 30;
              case '3': return 31;
              case '8': return 29;
              }
              break;
            }
            break;
          }
          break;
        }
        break;
      case 'S':case 's': return 11;
      }
      break;
    }
    break;
  case 'T':case 't':
    switch (*str++) {
    case 'R':case 'r': return 9;
    case 'Y':case 'y': return 5;
    }
    break;
  case 'U':case 'u': return 3;
  case 'V':case 'v': return 6;
  }
  return -1;
}
int tsctlEDIOCommandTextToBin(char *str) {
  switch (*str++) {
  case 'E':case 'e': return 11;
  case 'F':case 'f': return 1;
  case 'G':case 'g': return 12;
  case 'H':case 'h': return 13;
  case 'I':case 'i': return 0;
  case 'L':case 'l': return 2;
  case 'P':case 'p':
    switch (*str++) {
    case 'R':case 'r': return 4;
    case 'W':case 'w':
      switch (*str++) {
      case 'M':case 'm':
        switch (*str++) {
        case 0: return 6;
        case 'F':case 'f': return 8;
        }
        break;
      }
      break;
    }
    break;
  case 'Q':case 'q':
    switch (*str++) {
    case 'U':case 'u':
      switch (*str++) {
      case 'A':case 'a': return 10;
      case 'E':case 'e':
        switch (*str++) {
        case 'R':case 'r':
          switch (*str++) {
          case 'Y':case 'y':
            switch (*str++) {
            case 'F':case 'f': return 5;
            case 'P':case 'p':
              switch (*str++) {
              case 'W':case 'w':
                switch (*str++) {
                case 'M':case 'm':
                  switch (*str++) {
                  case 0: return 7;
                  case 'F':case 'f': return 9;
                  }
                  break;
                }
                break;
              }
              break;
            }
            break;
          }
          break;
        }
        break;
      }
      break;
    }
    break;
  case 'U':case 'u': return 3;
  }
  return -1;
}
int tsctlModeCommandTextToBin(char *str) {
  switch (*str++) {
  case 'A':case 'a':
    switch (*str++) {
    case 'B':case 'b':
      switch (*str++) {
      case 'I':case 'i':
        switch (*str++) {
        case 'N':case 'n':
          switch (*str++) {
          case 'H':case 'h': return 13;
          case 'O':case 'o': return 12;
          case 'U':case 'u': return 14;
          }
          break;
        }
        break;
      }
      break;
    case 'D':case 'd': return 10;
    case 'H':case 'h': return 9;
    case 'O':case 'o': return 11;
    case 'S':case 's':
      switch (*str++) {
      case 'S':case 's': return 3;
      case 'T':case 't': return 8;
      }
      break;
    }
    break;
  case 'D':case 'd': return 6;
  case 'F':case 'f': return 1;
  case 'H':case 'h': return 5;
  case 'I':case 'i': return 0;
  case 'J':case 'j': return 2;
  case 'N':case 'n': return 4;
  case 'O':case 'o': return 7;
  }
  return -1;
}
int (*tsctlCommand[61])(char *) = {
	tsctlSystemCommandTextToBin,
	tsctlBusCommandTextToBin,
	tsctlTimeCommandTextToBin,
	tsctlPinCommandTextToBin,
	tsctlDIORawCommandTextToBin,
	tsctlDIOCommandTextToBin,
	tsctlTWICommandTextToBin,
	tsctlCANCommandTextToBin,
	tsctlSPICommandTextToBin,
	tsctlAIOCommandTextToBin,
	tsctlEDIOCommandTextToBin,
	tsctlModeCommandTextToBin,
};
int WriteEnumPinMode(Stream *out,int val) {
  switch(val) {
  case 0: WriteF(out,"MODE_DIO"); break;
  case 1: WriteF(out,"MODE_CAN"); break;
  case 2: WriteF(out,"MODE_SPI"); break;
  case 3: WriteF(out,"MODE_ADC"); break;
  case 4: WriteF(out,"MODE_TWI"); break;
  case 5: WriteF(out,"MODE_UART"); break;
  case 6: WriteF(out,"MODE_TS"); break;
  case 7: WriteF(out,"MODE_BUS"); break;
  case 8: WriteF(out,"MODE_PWM"); break;
  case -1: WriteF(out,"MODE_UNKNOWN"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumPinError(Stream *out,int val) {
  switch(val) {
  case -100: WriteF(out,"PinErrorModeInvalid"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumDIOState(Stream *out,int val) {
  switch(val) {
  case -3: WriteF(out,"INPUT_LOW"); break;
  case -2: WriteF(out,"INPUT_HIGH"); break;
  case -1: WriteF(out,"INPUT"); break;
  case 0: WriteF(out,"LOW"); break;
  case 1: WriteF(out,"HIGH"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumDIOCaps(Stream *out,int val) {
  switch(val) {
  case 0: WriteF(out,"DIO_NOT_PRESENT"); break;
  case 1: WriteF(out,"DIO_CAN_INPUT"); break;
  case 2: WriteF(out,"DIO_CAN_DRIVE_HIGH"); break;
  case 3: WriteF(out,"DIO_HIGH_SIDE"); break;
  case 4: WriteF(out,"DIO_CAN_DRIVE_LOW"); break;
  case 5: WriteF(out,"DIO_LOW_SIDE"); break;
  case 6: WriteF(out,"DIO_OUTPUT_ONLY"); break;
  case 7: WriteF(out,"DIO_NORMAL"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumTWIMode(Stream *out,int val) {
  switch(val) {
  case 0: WriteF(out,"TWIModeSlave"); break;
  case 1: WriteF(out,"TWIModeMaster"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumTWIError(Stream *out,int val) {
  switch(val) {
  case -1: WriteF(out,"TWIErrorPortInvalid"); break;
  case -2: WriteF(out,"TWIErrorModeUnsupported"); break;
  case -3: WriteF(out,"TWIErrorBaudUnconstrained"); break;
  case -4: WriteF(out,"TWIErrorHardware"); break;
  case -5: WriteF(out,"TWIErrorHandle"); break;
  case -6: WriteF(out,"TWIErrorWriteNAck"); break;
  case -7: WriteF(out,"TWIErrorDataNAck"); break;
  case -8: WriteF(out,"TWIErrorReadNack"); break;
  case -9: WriteF(out,"TWIErrorSDALow"); break;
  case -10: WriteF(out,"TWIErrorSCLLow"); break;
  case -11: WriteF(out,"TWIErrorAdrsLen"); break;
  case -12: WriteF(out,"TWIErrorTimeout"); break;
  case -13: WriteF(out,"TWIErrorOverrun"); break;
  case -14: WriteF(out,"TWIErrorArbLost"); break;
  case -999: WriteF(out,"TWIErrorUnknown"); break;
  case -15: WriteF(out,"TWIErrorOpInvalid"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumTWIOps(Stream *out,int val) {
  switch(val) {
  case 0: WriteF(out,"TWIOpWrite"); break;
  case 1: WriteF(out,"TWIOpRead"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumCANEvent(Stream *out,int val) {
  int n = 0;
  if (val & 0x80) {
    WriteF(out,"%sCANEventBusError",n++?"+":"");
  }
  if (val & 0x40) {
    WriteF(out,"%sCANEventArbLost",n++?"+":"");
  }
  if (val & 0x20) {
    WriteF(out,"%sCANEventErrorPassive",n++?"+":"");
  }
  if (val & 0x10) {
    WriteF(out,"%sCANEventWakeUp",n++?"+":"");
  }
  if (val & 0x08) {
    WriteF(out,"%sCANEventDataOverrun",n++?"+":"");
  }
  if (val & 0x04) {
    WriteF(out,"%sCANEventErrorWarning",n++?"+":"");
  }
  if (val & 0x02) {
    WriteF(out,"%sCANEventTransmitDone",n++?"+":"");
  }
  if (val & 0x01) {
    WriteF(out,"%sCANEventReceiveReady",n++?"+":"");
  }
}
int WriteEnumCANFlags(Stream *out,int val) {
  int n = 0;
  if (val & 0x01) {
    WriteF(out,"%sFLAG_BUS_ERROR",n++?"+":"");
  }
  if (val & 0x02) {
    WriteF(out,"%sFLAG_ERROR_PASSIVE",n++?"+":"");
  }
  if (val & 0x04) {
    WriteF(out,"%sFLAG_DATA_OVERRUN",n++?"+":"");
  }
  if (val & 0x08) {
    WriteF(out,"%sFLAG_ERROR_WARNING",n++?"+":"");
  }
  if (val & 0x10) {
    WriteF(out,"%sFLAG_RTR",n++?"+":"");
  }
  if (val & 0x20) {
    WriteF(out,"%sFLAG_EXT_ID",n++?"+":"");
  }
  if (val & 0x40) {
    WriteF(out,"%sFLAG_LOCAL",n++?"+":"");
  }
  if (val & 0x80) {
    WriteF(out,"%sFLAG_CONTROL",n++?"+":"");
  }
}
int WriteEnumAIOType(Stream *out,int val) {
  int n = 0;
  if (val & 0x01) {
    WriteF(out,"%sAIO_ADC",n++?"+":"");
  }
  if (val & 0x02) {
    WriteF(out,"%sAIO_DAC",n++?"+":"");
  }
}
int WriteEnumEDIOType(Stream *out,int val) {
  switch(val) {
  case 1: WriteF(out,"EDIO_PWM"); break;
  case 2: WriteF(out,"EDIO_QUADRATURE"); break;
  case 3: WriteF(out,"EDIO_EDGECOUNT"); break;
  case 4: WriteF(out,"EDIO_GLITCHED"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumHBState(Stream *out,int val) {
  switch(val) {
  case 1: WriteF(out,"HB_LEFT"); break;
  case 2: WriteF(out,"HB_RIGHT"); break;
  case 3: WriteF(out,"HB_FREE_RUNNING"); break;
  case 4: WriteF(out,"HB_BRAKING"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumCacheBusError(Stream *out,int val) {
  switch(val) {
  case -100: WriteF(out,"CacheBusErrorWidthInvalid"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumCavium2132SBusError(Stream *out,int val) {
  switch(val) {
  case -100: WriteF(out,"Cavium2132SBusErrorMapping"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
int WriteEnumMMapBusError(Stream *out,int val) {
  switch(val) {
  case -100: WriteF(out,"MapBusErrorMapping"); break;
  default: WriteF(out,"%%d",val); break;
  }
}
void EnumInit() {
  System *sys = SystemInit(0);

  void add(char *name,int val) {
    char* tmp=ASCIIZ(name);
    sys->MapAdd(sys,tmp,val);
    ArrayFree(tmp);
  }
  add("MODE_DIO",0);
  add("MODE_CAN",1);
  add("MODE_SPI",2);
  add("MODE_ADC",3);
  add("MODE_TWI",4);
  add("MODE_UART",5);
  add("MODE_TS",6);
  add("MODE_BUS",7);
  add("MODE_PWM",8);
  add("MODE_UNKNOWN",-1);
  add("PinErrorModeInvalid",-100);
  add("INPUT_LOW",-3);
  add("INPUT_HIGH",-2);
  add("INPUT",-1);
  add("LOW",0);
  add("HIGH",1);
  add("DIO_NOT_PRESENT",0);
  add("DIO_CAN_INPUT",1);
  add("DIO_CAN_DRIVE_HIGH",2);
  add("DIO_HIGH_SIDE",3);
  add("DIO_CAN_DRIVE_LOW",4);
  add("DIO_LOW_SIDE",5);
  add("DIO_OUTPUT_ONLY",6);
  add("DIO_NORMAL",7);
  add("TWIModeSlave",0);
  add("TWIModeMaster",1);
  add("TWIErrorPortInvalid",-1);
  add("TWIErrorModeUnsupported",-2);
  add("TWIErrorBaudUnconstrained",-3);
  add("TWIErrorHardware",-4);
  add("TWIErrorHandle",-5);
  add("TWIErrorWriteNAck",-6);
  add("TWIErrorDataNAck",-7);
  add("TWIErrorReadNack",-8);
  add("TWIErrorSDALow",-9);
  add("TWIErrorSCLLow",-10);
  add("TWIErrorAdrsLen",-11);
  add("TWIErrorTimeout",-12);
  add("TWIErrorOverrun",-13);
  add("TWIErrorArbLost",-14);
  add("TWIErrorUnknown",-999);
  add("TWIErrorOpInvalid",-15);
  add("TWIOpWrite",0);
  add("TWIOpRead",1);
  add("CANEventBusError",128);
  add("CANEventArbLost",64);
  add("CANEventErrorPassive",32);
  add("CANEventWakeUp",16);
  add("CANEventDataOverrun",8);
  add("CANEventErrorWarning",4);
  add("CANEventTransmitDone",2);
  add("CANEventReceiveReady",1);
  add("FLAG_BUS_ERROR",1);
  add("FLAG_ERROR_PASSIVE",2);
  add("FLAG_DATA_OVERRUN",4);
  add("FLAG_ERROR_WARNING",8);
  add("FLAG_RTR",16);
  add("FLAG_EXT_ID",32);
  add("FLAG_LOCAL",64);
  add("FLAG_CONTROL",128);
  add("AIO_ADC",1);
  add("AIO_DAC",2);
  add("EDIO_PWM",1);
  add("EDIO_QUADRATURE",2);
  add("EDIO_EDGECOUNT",3);
  add("EDIO_GLITCHED",4);
  add("HB_LEFT",1);
  add("HB_RIGHT",2);
  add("HB_FREE_RUNNING",3);
  add("HB_BRAKING",4);
  add("CacheBusErrorWidthInvalid",-100);
  add("Cavium2132SBusErrorMapping",-100);
  add("MapBusErrorMapping",-100);
  add("System",0);
  add("Bus",1);
  add("Time",2);
  add("Pin",3);
  add("DIORaw",4);
  add("DIO",5);
  add("TWI",6);
  add("CAN",7);
  add("SPI",8);
  add("AIO",9);
  add("EDIO",10);
}
ArrayAuto(void *,WriteEnum,ARR(WriteEnumPinMode,WriteEnumPinError,WriteEnumDIOState,WriteEnumDIOCaps,WriteEnumTWIMode,WriteEnumTWIError,WriteEnumTWIOps,WriteEnumCANEvent,WriteEnumCANFlags,WriteEnumAIOType,WriteEnumEDIOType,WriteEnumHBState,WriteEnumCacheBusError,WriteEnumCavium2132SBusError,WriteEnumMMapBusError,));
ArrayAuto(void *,SystemClassCountArgs,ARR());
ArrayAuto(void *,SystemInstanceCountArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,SystemAPICountArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,SystemLockCountArgs,ARR());
ArrayAuto(void *,SystemLockHolderInfoArgs,ARR());
ArrayAuto(void *,SystemConnWaitInfoArgs,ARR());
ArrayAuto(void *,SystemCANBusGetArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,SystemBuildInfoArgs,ARR());
ArrayAuto(void *,SystemModelIdArgs,ARR());
ArrayAuto(void *,SystemBaseBoardIdArgs,ARR());
ArrayAuto(void *,SystemMapLengthArgs,ARR());
ArrayAuto(void *,SystemMapGetArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,SystemMapLookupArgs,ARR(tsctlArgParseArrayInt8,));
ArrayAuto(void *,SystemMapLookupPartialArgs,ARR(tsctlArgParseArrayInt8,tsctlArgParseInt32,));
ArrayAuto(void *,SystemMapAddArgs,ARR(tsctlArgParseArrayInt8,tsctlArgParseInt32,));
ArrayAuto(void *,SystemMapDeleteArgs,ARR(tsctlArgParseArrayInt8,));
ArrayAuto(void *,SystemNoteArgs,ARR(tsctlArgParseArrayInt8,));
ArrayAuto(void **,SystemArgs,ARR(ArrayL(SystemClassCountArgs),ArrayL(SystemInstanceCountArgs),ArrayL(SystemAPICountArgs),ArrayL(SystemLockCountArgs),ArrayL(SystemLockHolderInfoArgs),ArrayL(SystemConnWaitInfoArgs),ArrayL(SystemCANBusGetArgs),ArrayL(SystemBuildInfoArgs),ArrayL(SystemModelIdArgs),ArrayL(SystemBaseBoardIdArgs),ArrayL(SystemMapLengthArgs),ArrayL(SystemMapGetArgs),ArrayL(SystemMapLookupArgs),ArrayL(SystemMapLookupPartialArgs),ArrayL(SystemMapAddArgs),ArrayL(SystemMapDeleteArgs),ArrayL(SystemNoteArgs),));

ArrayAuto(void *,BusLockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusUnlockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusPreemptArgs,ARR());
ArrayAuto(void *,BusPeek8Args,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,BusPoke8Args,ARR(tsctlArgParseInt32,tsctlArgParseUInt8,));
ArrayAuto(void *,BusPeek16Args,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,BusPoke16Args,ARR(tsctlArgParseInt32,tsctlArgParseUInt16,));
ArrayAuto(void *,BusPeek32Args,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,BusPoke32Args,ARR(tsctlArgParseInt32,tsctlArgParseUInt32,));
ArrayAuto(void *,BusBitGet8Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitAssign8Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitSet8Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitClear8Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitGet16Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitAssign16Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitSet16Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitClear16Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitGet32Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitAssign32Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitSet32Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitClear32Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusPeekStreamArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusPokeStreamArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseArrayInt8,));
ArrayAuto(void *,BusRefreshArgs,ARR());
ArrayAuto(void *,BusCommitArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,BusBitToggle8Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitToggle16Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitToggle32Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusAssign8XArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusAssign16XArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusAssign32XArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitsGet8Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitsGet16Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,BusBitsGet32Args,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void **,BusArgs,ARR(ArrayL(BusLockArgs),ArrayL(BusUnlockArgs),ArrayL(BusPreemptArgs),ArrayL(BusPeek8Args),ArrayL(BusPoke8Args),ArrayL(BusPeek16Args),ArrayL(BusPoke16Args),ArrayL(BusPeek32Args),ArrayL(BusPoke32Args),ArrayL(BusBitGet8Args),ArrayL(BusBitAssign8Args),ArrayL(BusBitSet8Args),ArrayL(BusBitClear8Args),ArrayL(BusBitGet16Args),ArrayL(BusBitAssign16Args),ArrayL(BusBitSet16Args),ArrayL(BusBitClear16Args),ArrayL(BusBitGet32Args),ArrayL(BusBitAssign32Args),ArrayL(BusBitSet32Args),ArrayL(BusBitClear32Args),ArrayL(BusPeekStreamArgs),ArrayL(BusPokeStreamArgs),ArrayL(BusRefreshArgs),ArrayL(BusCommitArgs),ArrayL(BusBitToggle8Args),ArrayL(BusBitToggle16Args),ArrayL(BusBitToggle32Args),ArrayL(BusAssign8XArgs),ArrayL(BusAssign16XArgs),ArrayL(BusAssign32XArgs),ArrayL(BusBitsGet8Args),ArrayL(BusBitsGet16Args),ArrayL(BusBitsGet32Args),));

ArrayAuto(void *,TimeWaitArgs,ARR(tsctlArgParseUInt32,));
ArrayAuto(void *,TimeDelayArgs,ARR(tsctlArgParseUInt32,));
ArrayAuto(void *,TimeTickArgs,ARR());
ArrayAuto(void *,TimeusElapsedArgs,ARR(tsctlArgParseUInt32,));
ArrayAuto(void *,TimeusFutureArgs,ARR(tsctlArgParseUInt32,tsctlArgParseUInt32,));
ArrayAuto(void *,TimeTimeoutQArgs,ARR(tsctlArgParseUInt32,tsctlArgParseUInt32,));
ArrayAuto(void *,TimeTPSArgs,ARR());
ArrayAuto(void **,TimeArgs,ARR(ArrayL(TimeWaitArgs),ArrayL(TimeDelayArgs),ArrayL(TimeTickArgs),ArrayL(TimeusElapsedArgs),ArrayL(TimeusFutureArgs),ArrayL(TimeTimeoutQArgs),ArrayL(TimeTPSArgs),));

ArrayAuto(void *,PinLockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,PinUnlockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,PinPreemptArgs,ARR());
ArrayAuto(void *,PinModeGetArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,PinModeSetArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void **,PinArgs,ARR(ArrayL(PinLockArgs),ArrayL(PinUnlockArgs),ArrayL(PinPreemptArgs),ArrayL(PinModeGetArgs),ArrayL(PinModeSetArgs),));

ArrayAuto(void *,DIORawLockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,DIORawUnlockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,DIORawPreemptArgs,ARR());
ArrayAuto(void *,DIORawDirSetArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,DIORawDataSetArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,DIORawDirGetArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,DIORawDataGetArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,DIORawCountArgs,ARR());
ArrayAuto(void **,DIORawArgs,ARR(ArrayL(DIORawLockArgs),ArrayL(DIORawUnlockArgs),ArrayL(DIORawPreemptArgs),ArrayL(DIORawDirSetArgs),ArrayL(DIORawDataSetArgs),ArrayL(DIORawDirGetArgs),ArrayL(DIORawDataGetArgs),ArrayL(DIORawCountArgs),));

ArrayAuto(void *,DIOLockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,DIOUnlockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,DIOPreemptArgs,ARR());
ArrayAuto(void *,DIORefreshArgs,ARR());
ArrayAuto(void *,DIOCommitArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,DIOSetArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,DIOGetArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,DIOSetAsyncArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,DIOGetAsyncArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,DIOWaitArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseArrayInt32,tsctlArgParseArrayInt32,));
ArrayAuto(void *,DIOCountArgs,ARR());
ArrayAuto(void *,DIOCapabilitiesArgs,ARR(tsctlArgParseUInt32,));
ArrayAuto(void *,DIOGetMultiArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void **,DIOArgs,ARR(ArrayL(DIOLockArgs),ArrayL(DIOUnlockArgs),ArrayL(DIOPreemptArgs),ArrayL(DIORefreshArgs),ArrayL(DIOCommitArgs),ArrayL(DIOSetArgs),ArrayL(DIOGetArgs),ArrayL(DIOSetAsyncArgs),ArrayL(DIOGetAsyncArgs),ArrayL(DIOWaitArgs),ArrayL(DIOCountArgs),ArrayL(DIOCapabilitiesArgs),ArrayL(DIOGetMultiArgs),));

ArrayAuto(void *,TWILockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,TWIUnlockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,TWIPreemptArgs,ARR());
ArrayAuto(void *,TWIWriteArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseArrayInt8,));
ArrayAuto(void *,TWIReadArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void **,TWIArgs,ARR(ArrayL(TWILockArgs),ArrayL(TWIUnlockArgs),ArrayL(TWIPreemptArgs),ArrayL(TWIWriteArgs),ArrayL(TWIReadArgs),));

ArrayAuto(void *,CANRxArgs,ARR());
ArrayAuto(void *,CANTxArgs,ARR(tsctlArgParseUInt32,tsctlArgParseUInt32,tsctlArgParseArrayInt8,));
ArrayAuto(void *,CANBaudSetArgs,ARR(tsctlArgParseUInt32,));
ArrayAuto(void *,CANBaudGetArgs,ARR());
ArrayAuto(void *,CANAbortArgs,ARR());
ArrayAuto(void *,CANRxMultiArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void **,CANArgs,ARR(ArrayL(CANRxArgs),ArrayL(CANTxArgs),ArrayL(CANBaudSetArgs),ArrayL(CANBaudGetArgs),ArrayL(CANAbortArgs),ArrayL(CANRxMultiArgs),));

ArrayAuto(void *,SPILockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,SPIUnlockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,SPIPreemptArgs,ARR());
ArrayAuto(void *,SPIWriteArgs,ARR(tsctlArgParseInt32,tsctlArgParseArrayUInt8,));
ArrayAuto(void *,SPIReadArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,SPIReadWriteArgs,ARR(tsctlArgParseInt32,tsctlArgParseArrayUInt8,tsctlArgParseInt32,));
ArrayAuto(void *,SPIClockSetArgs,ARR(tsctlArgParseUInt32,));
ArrayAuto(void *,SPIEdgeSetArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void **,SPIArgs,ARR(ArrayL(SPILockArgs),ArrayL(SPIUnlockArgs),ArrayL(SPIPreemptArgs),ArrayL(SPIWriteArgs),ArrayL(SPIReadArgs),ArrayL(SPIReadWriteArgs),ArrayL(SPIClockSetArgs),ArrayL(SPIEdgeSetArgs),));

ArrayAuto(void *,AIOLockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,AIOUnlockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,AIOPreemptArgs,ARR());
ArrayAuto(void *,AIOTypeArgs,ARR());
ArrayAuto(void *,AIOVoltageRangeListArgs,ARR());
ArrayAuto(void *,AIOPrecisionListArgs,ARR());
ArrayAuto(void *,AIOPeriodRangeListArgs,ARR());
ArrayAuto(void *,AIOTriggerListArgs,ARR());
ArrayAuto(void *,AIOChannelsArgs,ARR());
ArrayAuto(void *,AIOResetArgs,ARR());
ArrayAuto(void *,AIOChannelEnableArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,AIOChannelSamplePeriodArgs,ARR(tsctlArgParseInt32,tsctlArgParseUInt32,));
ArrayAuto(void *,AIOChannelPrecisionArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,AIOChannelVoltageRangeArgs,ARR(tsctlArgParseInt32,tsctlArgParseReal32,tsctlArgParseReal32,));
ArrayAuto(void *,AIOConfigurationArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,AIOConfigureTestArgs,ARR(tsctlArgParseArrayReal32,tsctlArgParseArrayReal32,tsctlArgParseArrayInt32,tsctlArgParseArrayInt32,tsctlArgParseArrayInt32,tsctlArgParseInt32,));
ArrayAuto(void *,AIOConfigureArgs,ARR(tsctlArgParseArrayReal32,tsctlArgParseArrayReal32,tsctlArgParseArrayInt32,tsctlArgParseArrayInt32,tsctlArgParseArrayInt32,tsctlArgParseInt32,));
ArrayAuto(void *,AIOITrigArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,AIOGetArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,AIOPutArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,AIOReadyArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,AIOGets8Args,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,AIOGets16Args,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,AIOGets32Args,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,AIOPuts8Args,ARR(tsctlArgParseArrayInt8,));
ArrayAuto(void *,AIOPuts16Args,ARR(tsctlArgParseArrayInt16,));
ArrayAuto(void *,AIOPuts32Args,ARR(tsctlArgParseArrayInt32,));
ArrayAuto(void *,AIOReadys8Args,ARR(tsctlArgParseArrayInt8,));
ArrayAuto(void *,AIOReadys16Args,ARR(tsctlArgParseArrayInt16,));
ArrayAuto(void *,AIOReadys32Args,ARR(tsctlArgParseArrayInt32,));
ArrayAuto(void **,AIOArgs,ARR(ArrayL(AIOLockArgs),ArrayL(AIOUnlockArgs),ArrayL(AIOPreemptArgs),ArrayL(AIOTypeArgs),ArrayL(AIOVoltageRangeListArgs),ArrayL(AIOPrecisionListArgs),ArrayL(AIOPeriodRangeListArgs),ArrayL(AIOTriggerListArgs),ArrayL(AIOChannelsArgs),ArrayL(AIOResetArgs),ArrayL(AIOChannelEnableArgs),ArrayL(AIOChannelSamplePeriodArgs),ArrayL(AIOChannelPrecisionArgs),ArrayL(AIOChannelVoltageRangeArgs),ArrayL(AIOConfigurationArgs),ArrayL(AIOConfigureTestArgs),ArrayL(AIOConfigureArgs),ArrayL(AIOITrigArgs),ArrayL(AIOGetArgs),ArrayL(AIOPutArgs),ArrayL(AIOReadyArgs),ArrayL(AIOGets8Args),ArrayL(AIOGets16Args),ArrayL(AIOGets32Args),ArrayL(AIOPuts8Args),ArrayL(AIOPuts16Args),ArrayL(AIOPuts32Args),ArrayL(AIOReadys8Args),ArrayL(AIOReadys16Args),ArrayL(AIOReadys32Args),));

ArrayAuto(void *,EDIOLockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,EDIOUnlockArgs,ARR(tsctlArgParseUInt32,tsctlArgParseInt32,));
ArrayAuto(void *,EDIOPreemptArgs,ARR());
ArrayAuto(void *,EDIOQueryFunctionArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,EDIOPWMArgs,ARR(tsctlArgParseInt32,tsctlArgParseUInt32,tsctlArgParseUInt32,));
ArrayAuto(void *,EDIOQueryPWMArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,EDIOPWMfdArgs,ARR(tsctlArgParseInt32,tsctlArgParseUInt32,tsctlArgParseUInt32,));
ArrayAuto(void *,EDIOQueryPWMfdArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,EDIOQuadratureCountArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,EDIOEdgeCountArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void *,EDIOGlitchedArgs,ARR(tsctlArgParseInt32,));
ArrayAuto(void *,EDIOHBridgeArgs,ARR(tsctlArgParseInt32,tsctlArgParseInt32,));
ArrayAuto(void **,EDIOArgs,ARR(ArrayL(EDIOLockArgs),ArrayL(EDIOUnlockArgs),ArrayL(EDIOPreemptArgs),ArrayL(EDIOQueryFunctionArgs),ArrayL(EDIOPWMArgs),ArrayL(EDIOQueryPWMArgs),ArrayL(EDIOPWMfdArgs),ArrayL(EDIOQueryPWMfdArgs),ArrayL(EDIOQuadratureCountArgs),ArrayL(EDIOEdgeCountArgs),ArrayL(EDIOGlitchedArgs),ArrayL(EDIOHBridgeArgs),));

ArrayAuto(void *,ModeJSONArgs,ARR());
ArrayAuto(void *,ModeAssignArgs,ARR());
ArrayAuto(void *,ModeNoAssignArgs,ARR());
ArrayAuto(void *,ModeHexArgs,ARR());
ArrayAuto(void *,ModeDecArgs,ARR());
ArrayAuto(void *,ModeOctArgs,ARR());
ArrayAuto(void *,ModeAStrArgs,ARR());
ArrayAuto(void *,ModeAHexArgs,ARR());
ArrayAuto(void *,ModeADecArgs,ARR());
ArrayAuto(void *,ModeAOctArgs,ARR());
ArrayAuto(void *,ModeABinOctArgs,ARR());
ArrayAuto(void *,ModeABinHexArgs,ARR());
ArrayAuto(void *,ModeABinUniArgs,ARR());
ArrayAuto(void **,ModeArgs,ARR(ArrayL(ModeJSONArgs),ArrayL(ModeAssignArgs),ArrayL(ModeNoAssignArgs),ArrayL(ModeHexArgs),ArrayL(ModeDecArgs),ArrayL(ModeOctArgs),ArrayL(ModeAStrArgs),ArrayL(ModeAHexArgs),ArrayL(ModeADecArgs),ArrayL(ModeAOctArgs),ArrayL(ModeABinOctArgs),ArrayL(ModeABinHexArgs),ArrayL(ModeABinUniArgs),));

ArrayAuto(void***,Args,ARR(ArrayL(SystemArgs),ArrayL(BusArgs),ArrayL(TimeArgs),ArrayL(PinArgs),ArrayL(DIORawArgs),ArrayL(DIOArgs),ArrayL(TWIArgs),ArrayL(CANArgs),ArrayL(SPIArgs),ArrayL(AIOArgs),ArrayL(EDIOArgs),ArrayL(ModeArgs),));

ArrayAuto(char*,SystemClassCountArgNames,ARR());
ArrayAuto(char*,SystemInstanceCountArgNames,ARR("ClassNumber",));
ArrayAuto(char*,SystemAPICountArgNames,ARR("ClassNumber",));
ArrayAuto(char*,SystemLockCountArgNames,ARR());
ArrayAuto(char*,SystemLockHolderInfoArgNames,ARR());
ArrayAuto(char*,SystemConnWaitInfoArgNames,ARR());
ArrayAuto(char*,SystemCANBusGetArgNames,ARR("CANInstance",));
ArrayAuto(char*,SystemBuildInfoArgNames,ARR());
ArrayAuto(char*,SystemModelIdArgNames,ARR());
ArrayAuto(char*,SystemBaseBoardIdArgNames,ARR());
ArrayAuto(char*,SystemMapLengthArgNames,ARR());
ArrayAuto(char*,SystemMapGetArgNames,ARR("MapIndex",));
ArrayAuto(char*,SystemMapLookupArgNames,ARR("String",));
ArrayAuto(char*,SystemMapLookupPartialArgNames,ARR("StringPrefix","Value",));
ArrayAuto(char*,SystemMapAddArgNames,ARR("String","Value",));
ArrayAuto(char*,SystemMapDeleteArgNames,ARR("String",));
ArrayAuto(char*,SystemNoteArgNames,ARR("Message",));
ArrayAuto(char**,SystemArgNames,ARR(ArrayL(SystemClassCountArgNames),ArrayL(SystemInstanceCountArgNames),ArrayL(SystemAPICountArgNames),ArrayL(SystemLockCountArgNames),ArrayL(SystemLockHolderInfoArgNames),ArrayL(SystemConnWaitInfoArgNames),ArrayL(SystemCANBusGetArgNames),ArrayL(SystemBuildInfoArgNames),ArrayL(SystemModelIdArgNames),ArrayL(SystemBaseBoardIdArgNames),ArrayL(SystemMapLengthArgNames),ArrayL(SystemMapGetArgNames),ArrayL(SystemMapLookupArgNames),ArrayL(SystemMapLookupPartialArgNames),ArrayL(SystemMapAddArgNames),ArrayL(SystemMapDeleteArgNames),ArrayL(SystemNoteArgNames),));

ArrayAuto(char*,BusLockArgNames,ARR("num","flags",));
ArrayAuto(char*,BusUnlockArgNames,ARR("num","flags",));
ArrayAuto(char*,BusPreemptArgNames,ARR());
ArrayAuto(char*,BusPeek8ArgNames,ARR("Address",));
ArrayAuto(char*,BusPoke8ArgNames,ARR("Address","Value",));
ArrayAuto(char*,BusPeek16ArgNames,ARR("Address",));
ArrayAuto(char*,BusPoke16ArgNames,ARR("Address","Value",));
ArrayAuto(char*,BusPeek32ArgNames,ARR("Address",));
ArrayAuto(char*,BusPoke32ArgNames,ARR("Address","Value",));
ArrayAuto(char*,BusBitGet8ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitAssign8ArgNames,ARR("Address","BitNumber","Value",));
ArrayAuto(char*,BusBitSet8ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitClear8ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitGet16ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitAssign16ArgNames,ARR("Address","BitNumber","Value",));
ArrayAuto(char*,BusBitSet16ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitClear16ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitGet32ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitAssign32ArgNames,ARR("Address","BitNumber","Value",));
ArrayAuto(char*,BusBitSet32ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitClear32ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusPeekStreamArgNames,ARR("address","direction","dest_length",));
ArrayAuto(char*,BusPokeStreamArgNames,ARR("address","direction","data",));
ArrayAuto(char*,BusRefreshArgNames,ARR());
ArrayAuto(char*,BusCommitArgNames,ARR("ForceAll",));
ArrayAuto(char*,BusBitToggle8ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitToggle16ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusBitToggle32ArgNames,ARR("Address","BitNumber",));
ArrayAuto(char*,BusAssign8XArgNames,ARR("Address","BitMSB","BitLSB","Value",));
ArrayAuto(char*,BusAssign16XArgNames,ARR("Address","BitMSB","BitLSB","Value",));
ArrayAuto(char*,BusAssign32XArgNames,ARR("Address","BitMSB","BitLSB","Value",));
ArrayAuto(char*,BusBitsGet8ArgNames,ARR("Address","BitMSB","BitLSB",));
ArrayAuto(char*,BusBitsGet16ArgNames,ARR("Address","BitMSB","BitLSB",));
ArrayAuto(char*,BusBitsGet32ArgNames,ARR("Address","BitMSB","BitLSB",));
ArrayAuto(char**,BusArgNames,ARR(ArrayL(BusLockArgNames),ArrayL(BusUnlockArgNames),ArrayL(BusPreemptArgNames),ArrayL(BusPeek8ArgNames),ArrayL(BusPoke8ArgNames),ArrayL(BusPeek16ArgNames),ArrayL(BusPoke16ArgNames),ArrayL(BusPeek32ArgNames),ArrayL(BusPoke32ArgNames),ArrayL(BusBitGet8ArgNames),ArrayL(BusBitAssign8ArgNames),ArrayL(BusBitSet8ArgNames),ArrayL(BusBitClear8ArgNames),ArrayL(BusBitGet16ArgNames),ArrayL(BusBitAssign16ArgNames),ArrayL(BusBitSet16ArgNames),ArrayL(BusBitClear16ArgNames),ArrayL(BusBitGet32ArgNames),ArrayL(BusBitAssign32ArgNames),ArrayL(BusBitSet32ArgNames),ArrayL(BusBitClear32ArgNames),ArrayL(BusPeekStreamArgNames),ArrayL(BusPokeStreamArgNames),ArrayL(BusRefreshArgNames),ArrayL(BusCommitArgNames),ArrayL(BusBitToggle8ArgNames),ArrayL(BusBitToggle16ArgNames),ArrayL(BusBitToggle32ArgNames),ArrayL(BusAssign8XArgNames),ArrayL(BusAssign16XArgNames),ArrayL(BusAssign32XArgNames),ArrayL(BusBitsGet8ArgNames),ArrayL(BusBitsGet16ArgNames),ArrayL(BusBitsGet32ArgNames),));

ArrayAuto(char*,TimeWaitArgNames,ARR("microseconds",));
ArrayAuto(char*,TimeDelayArgNames,ARR("microseconds",));
ArrayAuto(char*,TimeTickArgNames,ARR());
ArrayAuto(char*,TimeusElapsedArgNames,ARR("start",));
ArrayAuto(char*,TimeusFutureArgNames,ARR("start","microseconds",));
ArrayAuto(char*,TimeTimeoutQArgNames,ARR("start","end",));
ArrayAuto(char*,TimeTPSArgNames,ARR());
ArrayAuto(char**,TimeArgNames,ARR(ArrayL(TimeWaitArgNames),ArrayL(TimeDelayArgNames),ArrayL(TimeTickArgNames),ArrayL(TimeusElapsedArgNames),ArrayL(TimeusFutureArgNames),ArrayL(TimeTimeoutQArgNames),ArrayL(TimeTPSArgNames),));

ArrayAuto(char*,PinLockArgNames,ARR("num","flags",));
ArrayAuto(char*,PinUnlockArgNames,ARR("num","flags",));
ArrayAuto(char*,PinPreemptArgNames,ARR());
ArrayAuto(char*,PinModeGetArgNames,ARR("PinNumber",));
ArrayAuto(char*,PinModeSetArgNames,ARR("PinNumber","Mode",));
ArrayAuto(char**,PinArgNames,ARR(ArrayL(PinLockArgNames),ArrayL(PinUnlockArgNames),ArrayL(PinPreemptArgNames),ArrayL(PinModeGetArgNames),ArrayL(PinModeSetArgNames),));

ArrayAuto(char*,DIORawLockArgNames,ARR("num","flags",));
ArrayAuto(char*,DIORawUnlockArgNames,ARR("num","flags",));
ArrayAuto(char*,DIORawPreemptArgNames,ARR());
ArrayAuto(char*,DIORawDirSetArgNames,ARR("num","asOutput",));
ArrayAuto(char*,DIORawDataSetArgNames,ARR("num","asHigh",));
ArrayAuto(char*,DIORawDirGetArgNames,ARR("num",));
ArrayAuto(char*,DIORawDataGetArgNames,ARR("num",));
ArrayAuto(char*,DIORawCountArgNames,ARR());
ArrayAuto(char**,DIORawArgNames,ARR(ArrayL(DIORawLockArgNames),ArrayL(DIORawUnlockArgNames),ArrayL(DIORawPreemptArgNames),ArrayL(DIORawDirSetArgNames),ArrayL(DIORawDataSetArgNames),ArrayL(DIORawDirGetArgNames),ArrayL(DIORawDataGetArgNames),ArrayL(DIORawCountArgNames),));

ArrayAuto(char*,DIOLockArgNames,ARR("num","flags",));
ArrayAuto(char*,DIOUnlockArgNames,ARR("num","flags",));
ArrayAuto(char*,DIOPreemptArgNames,ARR());
ArrayAuto(char*,DIORefreshArgNames,ARR());
ArrayAuto(char*,DIOCommitArgNames,ARR("ForceAll",));
ArrayAuto(char*,DIOSetArgNames,ARR("DIONum","State",));
ArrayAuto(char*,DIOGetArgNames,ARR("DIONum",));
ArrayAuto(char*,DIOSetAsyncArgNames,ARR("DIONum","State",));
ArrayAuto(char*,DIOGetAsyncArgNames,ARR("DIONum",));
ArrayAuto(char*,DIOWaitArgNames,ARR("match_length","min","max","nh","nl",));
ArrayAuto(char*,DIOCountArgNames,ARR());
ArrayAuto(char*,DIOCapabilitiesArgNames,ARR("num",));
ArrayAuto(char*,DIOGetMultiArgNames,ARR("state_length","offset",));
ArrayAuto(char**,DIOArgNames,ARR(ArrayL(DIOLockArgNames),ArrayL(DIOUnlockArgNames),ArrayL(DIOPreemptArgNames),ArrayL(DIORefreshArgNames),ArrayL(DIOCommitArgNames),ArrayL(DIOSetArgNames),ArrayL(DIOGetArgNames),ArrayL(DIOSetAsyncArgNames),ArrayL(DIOGetAsyncArgNames),ArrayL(DIOWaitArgNames),ArrayL(DIOCountArgNames),ArrayL(DIOCapabilitiesArgNames),ArrayL(DIOGetMultiArgNames),));

ArrayAuto(char*,TWILockArgNames,ARR("num","flags",));
ArrayAuto(char*,TWIUnlockArgNames,ARR("num","flags",));
ArrayAuto(char*,TWIPreemptArgNames,ARR());
ArrayAuto(char*,TWIWriteArgNames,ARR("devadr","adrslen","adrs","bytes",));
ArrayAuto(char*,TWIReadArgNames,ARR("devadr","adrslen","adrs","bytes_length",));
ArrayAuto(char**,TWIArgNames,ARR(ArrayL(TWILockArgNames),ArrayL(TWIUnlockArgNames),ArrayL(TWIPreemptArgNames),ArrayL(TWIWriteArgNames),ArrayL(TWIReadArgNames),));

ArrayAuto(char*,CANRxArgNames,ARR());
ArrayAuto(char*,CANTxArgNames,ARR("flags","id","data",));
ArrayAuto(char*,CANBaudSetArgNames,ARR("opt_baud",));
ArrayAuto(char*,CANBaudGetArgNames,ARR());
ArrayAuto(char*,CANAbortArgNames,ARR());
ArrayAuto(char*,CANRxMultiArgNames,ARR("msg_length","min",));
ArrayAuto(char**,CANArgNames,ARR(ArrayL(CANRxArgNames),ArrayL(CANTxArgNames),ArrayL(CANBaudSetArgNames),ArrayL(CANBaudGetArgNames),ArrayL(CANAbortArgNames),ArrayL(CANRxMultiArgNames),));

ArrayAuto(char*,SPILockArgNames,ARR("num","flags",));
ArrayAuto(char*,SPIUnlockArgNames,ARR("num","flags",));
ArrayAuto(char*,SPIPreemptArgNames,ARR());
ArrayAuto(char*,SPIWriteArgNames,ARR("adrs","buf",));
ArrayAuto(char*,SPIReadArgNames,ARR("adrs","buf_length",));
ArrayAuto(char*,SPIReadWriteArgNames,ARR("adrs","wbuf","rbuf_length",));
ArrayAuto(char*,SPIClockSetArgNames,ARR("hz",));
ArrayAuto(char*,SPIEdgeSetArgNames,ARR("posedge",));
ArrayAuto(char**,SPIArgNames,ARR(ArrayL(SPILockArgNames),ArrayL(SPIUnlockArgNames),ArrayL(SPIPreemptArgNames),ArrayL(SPIWriteArgNames),ArrayL(SPIReadArgNames),ArrayL(SPIReadWriteArgNames),ArrayL(SPIClockSetArgNames),ArrayL(SPIEdgeSetArgNames),));

ArrayAuto(char*,AIOLockArgNames,ARR("num","flags",));
ArrayAuto(char*,AIOUnlockArgNames,ARR("num","flags",));
ArrayAuto(char*,AIOPreemptArgNames,ARR());
ArrayAuto(char*,AIOTypeArgNames,ARR());
ArrayAuto(char*,AIOVoltageRangeListArgNames,ARR());
ArrayAuto(char*,AIOPrecisionListArgNames,ARR());
ArrayAuto(char*,AIOPeriodRangeListArgNames,ARR());
ArrayAuto(char*,AIOTriggerListArgNames,ARR());
ArrayAuto(char*,AIOChannelsArgNames,ARR());
ArrayAuto(char*,AIOResetArgNames,ARR());
ArrayAuto(char*,AIOChannelEnableArgNames,ARR("ch","flag",));
ArrayAuto(char*,AIOChannelSamplePeriodArgNames,ARR("ch","ns",));
ArrayAuto(char*,AIOChannelPrecisionArgNames,ARR("ch","prec",));
ArrayAuto(char*,AIOChannelVoltageRangeArgNames,ARR("ch","low","high",));
ArrayAuto(char*,AIOConfigurationArgNames,ARR("low_length","high_length","prec_length","t_length","trigger_length",));
ArrayAuto(char*,AIOConfigureTestArgNames,ARR("low","high","prec","rate","trigger","itrig",));
ArrayAuto(char*,AIOConfigureArgNames,ARR("low","high","prec","rate","trigger","itrig",));
ArrayAuto(char*,AIOITrigArgNames,ARR("itrig",));
ArrayAuto(char*,AIOGetArgNames,ARR("channel",));
ArrayAuto(char*,AIOPutArgNames,ARR("channel","value",));
ArrayAuto(char*,AIOReadyArgNames,ARR("channel",));
ArrayAuto(char*,AIOGets8ArgNames,ARR("buf_length",));
ArrayAuto(char*,AIOGets16ArgNames,ARR("buf_length",));
ArrayAuto(char*,AIOGets32ArgNames,ARR("buf_length",));
ArrayAuto(char*,AIOPuts8ArgNames,ARR("buf",));
ArrayAuto(char*,AIOPuts16ArgNames,ARR("buf",));
ArrayAuto(char*,AIOPuts32ArgNames,ARR("buf",));
ArrayAuto(char*,AIOReadys8ArgNames,ARR("buf",));
ArrayAuto(char*,AIOReadys16ArgNames,ARR("buf",));
ArrayAuto(char*,AIOReadys32ArgNames,ARR("buf",));
ArrayAuto(char**,AIOArgNames,ARR(ArrayL(AIOLockArgNames),ArrayL(AIOUnlockArgNames),ArrayL(AIOPreemptArgNames),ArrayL(AIOTypeArgNames),ArrayL(AIOVoltageRangeListArgNames),ArrayL(AIOPrecisionListArgNames),ArrayL(AIOPeriodRangeListArgNames),ArrayL(AIOTriggerListArgNames),ArrayL(AIOChannelsArgNames),ArrayL(AIOResetArgNames),ArrayL(AIOChannelEnableArgNames),ArrayL(AIOChannelSamplePeriodArgNames),ArrayL(AIOChannelPrecisionArgNames),ArrayL(AIOChannelVoltageRangeArgNames),ArrayL(AIOConfigurationArgNames),ArrayL(AIOConfigureTestArgNames),ArrayL(AIOConfigureArgNames),ArrayL(AIOITrigArgNames),ArrayL(AIOGetArgNames),ArrayL(AIOPutArgNames),ArrayL(AIOReadyArgNames),ArrayL(AIOGets8ArgNames),ArrayL(AIOGets16ArgNames),ArrayL(AIOGets32ArgNames),ArrayL(AIOPuts8ArgNames),ArrayL(AIOPuts16ArgNames),ArrayL(AIOPuts32ArgNames),ArrayL(AIOReadys8ArgNames),ArrayL(AIOReadys16ArgNames),ArrayL(AIOReadys32ArgNames),));

ArrayAuto(char*,EDIOLockArgNames,ARR("num","flags",));
ArrayAuto(char*,EDIOUnlockArgNames,ARR("num","flags",));
ArrayAuto(char*,EDIOPreemptArgNames,ARR());
ArrayAuto(char*,EDIOQueryFunctionArgNames,ARR("type",));
ArrayAuto(char*,EDIOPWMArgNames,ARR("num","periodHigh","periodLow",));
ArrayAuto(char*,EDIOQueryPWMArgNames,ARR("num",));
ArrayAuto(char*,EDIOPWMfdArgNames,ARR("num","freq","DC",));
ArrayAuto(char*,EDIOQueryPWMfdArgNames,ARR("num",));
ArrayAuto(char*,EDIOQuadratureCountArgNames,ARR("num",));
ArrayAuto(char*,EDIOEdgeCountArgNames,ARR("num","edge",));
ArrayAuto(char*,EDIOGlitchedArgNames,ARR("num",));
ArrayAuto(char*,EDIOHBridgeArgNames,ARR("num","state",));
ArrayAuto(char**,EDIOArgNames,ARR(ArrayL(EDIOLockArgNames),ArrayL(EDIOUnlockArgNames),ArrayL(EDIOPreemptArgNames),ArrayL(EDIOQueryFunctionArgNames),ArrayL(EDIOPWMArgNames),ArrayL(EDIOQueryPWMArgNames),ArrayL(EDIOPWMfdArgNames),ArrayL(EDIOQueryPWMfdArgNames),ArrayL(EDIOQuadratureCountArgNames),ArrayL(EDIOEdgeCountArgNames),ArrayL(EDIOGlitchedArgNames),ArrayL(EDIOHBridgeArgNames),));

ArrayAuto(char*,ModeJSONArgNames,ARR());
ArrayAuto(char*,ModeAssignArgNames,ARR());
ArrayAuto(char*,ModeNoAssignArgNames,ARR());
ArrayAuto(char*,ModeHexArgNames,ARR());
ArrayAuto(char*,ModeDecArgNames,ARR());
ArrayAuto(char*,ModeOctArgNames,ARR());
ArrayAuto(char*,ModeAStrArgNames,ARR());
ArrayAuto(char*,ModeAHexArgNames,ARR());
ArrayAuto(char*,ModeADecArgNames,ARR());
ArrayAuto(char*,ModeAOctArgNames,ARR());
ArrayAuto(char*,ModeABinOctArgNames,ARR());
ArrayAuto(char*,ModeABinHexArgNames,ARR());
ArrayAuto(char*,ModeABinUniArgNames,ARR());
ArrayAuto(char**,ModeArgNames,ARR(ArrayL(ModeJSONArgNames),ArrayL(ModeAssignArgNames),ArrayL(ModeNoAssignArgNames),ArrayL(ModeHexArgNames),ArrayL(ModeDecArgNames),ArrayL(ModeOctArgNames),ArrayL(ModeAStrArgNames),ArrayL(ModeAHexArgNames),ArrayL(ModeADecArgNames),ArrayL(ModeAOctArgNames),ArrayL(ModeABinOctArgNames),ArrayL(ModeABinHexArgNames),ArrayL(ModeABinUniArgNames),));

ArrayAuto(char***,ArgNames,ARR(ArrayL(SystemArgNames),ArrayL(BusArgNames),ArrayL(TimeArgNames),ArrayL(PinArgNames),ArrayL(DIORawArgNames),ArrayL(DIOArgNames),ArrayL(TWIArgNames),ArrayL(CANArgNames),ArrayL(SPIArgNames),ArrayL(AIOArgNames),ArrayL(EDIOArgNames),ArrayL(ModeArgNames),));

int tsctlSystemClassCount(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,0);
  int32 ret;
  ret = ob->ClassCount(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemInstanceCount(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,1);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->InstanceCount(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemAPICount(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,2);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->APICount(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemLockCount(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,3);
  int32 ret;
  ret = ob->LockCount(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemLockHolderInfo(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,4);
  LockHolderInf* ret;
  ret = ob->LockHolderInfo(ob);
  WriteInt8LE(out,0x70);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt8LE(out,0x13);
      WriteInt32LE(out,ret[i].pid);
      WriteInt8LE(out,0x13);
      WriteInt32LE(out,ret[i].count);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemConnWaitInfo(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,5);
  ConnectionWaitInf* ret;
  ret = ob->ConnWaitInfo(ob);
  WriteInt8LE(out,0x70);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt8LE(out,0x13);
      WriteInt32LE(out,ret[i].pid);
      WriteInt8LE(out,0x13);
      WriteInt32LE(out,ret[i].wait);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemCANBusGet(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,6);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->CANBusGet(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemBuildInfo(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,7);
  BuildInf arg1[1];
  ob->BuildInfo(ob,arg1);
  WriteInt8LE(out,0x73);
  WriteInt32LE(out,1);
  {
    int i;
    for(i=0;i<1;i++) {
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].buildNumber);
      WriteInt8LE(out,0x13);
      WriteInt32LE(out,arg1[i].buildTime);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].uptime);
      WriteInt8LE(out,0x50);
      WriteInt32LE(out,ArrayLength(arg1[i].hostname));
      {
        int k;
        for(k=0;k<ArrayLength(arg1[i].hostname);k++) {
          WriteInt8LE(out,arg1[i].hostname[k]);
        }
      }
      WriteInt8LE(out,0x50);
      WriteInt32LE(out,ArrayLength(arg1[i].arch));
      {
        int k;
        for(k=0;k<ArrayLength(arg1[i].arch);k++) {
          WriteInt8LE(out,arg1[i].arch[k]);
        }
      }
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemModelId(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,8);
  int32 ret;
  ret = ob->ModelId(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemBaseBoardId(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,9);
  int32 ret;
  ret = ob->BaseBoardId(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemMapLength(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,10);
  int32 ret;
  ret = ob->MapLength(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemMapGet(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,11);
  int8* ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2[1];
  ret = ob->MapGet(ob,arg1,arg2);
  WriteInt8LE(out,0x50);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt8LE(out,ret[i]);
    }
  }
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,1);
  {
    int i;
    for(i=0;i<1;i++) {
      WriteInt32LE(out,arg2[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemMapLookup(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,12);
  int32 ret;
  const int8* arg1 = ReadArrayInt8LE(in);
  ret = ob->MapLookup(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemMapLookupPartial(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,13);
  int8* ret;
  const int8* arg1 = ReadArrayInt8LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->MapLookupPartial(ob,arg1,arg2);
  WriteInt8LE(out,0x50);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt8LE(out,ret[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemMapAdd(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,14);
  int32 ret;
  const int8* arg1 = ReadArrayInt8LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->MapAdd(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemMapDelete(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,15);
  int32 ret;
  const int8* arg1 = ReadArrayInt8LE(in);
  ret = ob->MapDelete(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSystemNote(System *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,0);
  WriteInt8LE(out,16);
  int8* ret;
  const int8* arg1 = ReadArrayInt8LE(in);
  ret = ob->Note(ob,arg1);
  WriteInt8LE(out,0x50);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt8LE(out,ret[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlSystem,ARR((void *)tsctlSystemClassCount,(void *)tsctlSystemInstanceCount,(void *)tsctlSystemAPICount,(void *)tsctlSystemLockCount,(void *)tsctlSystemLockHolderInfo,(void *)tsctlSystemConnWaitInfo,(void *)tsctlSystemCANBusGet,(void *)tsctlSystemBuildInfo,(void *)tsctlSystemModelId,(void *)tsctlSystemBaseBoardId,(void *)tsctlSystemMapLength,(void *)tsctlSystemMapGet,(void *)tsctlSystemMapLookup,(void *)tsctlSystemMapLookupPartial,(void *)tsctlSystemMapAdd,(void *)tsctlSystemMapDelete,(void *)tsctlSystemNote,));

int tsctlBusLock(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,0);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Lock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusUnlock(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Unlock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPreempt(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,2);
  int32 ret;
  ret = ob->Preempt(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPeek8(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,3);
  uint8 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->Peek8(ob,arg1);
  WriteInt8LE(out,0x00);
  WriteUInt8LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPoke8(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,4);
  int32 arg1 = ReadInt32LE(in);
  uint8 arg2 = ReadUInt8LE(in);
  ob->Poke8(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPeek16(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,5);
  uint16 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->Peek16(ob,arg1);
  WriteInt8LE(out,0x01);
  WriteUInt16LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPoke16(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,6);
  int32 arg1 = ReadInt32LE(in);
  uint16 arg2 = ReadUInt16LE(in);
  ob->Poke16(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPeek32(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,7);
  uint32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->Peek32(ob,arg1);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPoke32(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,8);
  int32 arg1 = ReadInt32LE(in);
  uint32 arg2 = ReadUInt32LE(in);
  ob->Poke32(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitGet8(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,9);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->BitGet8(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitAssign8(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,10);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  ob->BitAssign8(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitSet8(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,11);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ob->BitSet8(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitClear8(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,12);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ob->BitClear8(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitGet16(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,13);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->BitGet16(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitAssign16(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,14);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  ob->BitAssign16(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitSet16(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,15);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ob->BitSet16(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitClear16(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,16);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ob->BitClear16(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitGet32(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,17);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->BitGet32(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitAssign32(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,18);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  ob->BitAssign32(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitSet32(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,19);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ob->BitSet32(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitClear32(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,20);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ob->BitClear32(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPeekStream(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,21);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int len3 = ReadInt32LE(in);
  int8* arg3 = ArrayAlloc(len3,sizeof(int8));
  ob->PeekStream(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x50);
  WriteInt32LE(out,ArrayLength(arg3));
  {
    int i;
    for(i=0;i<ArrayLength(arg3);i++) {
      WriteInt8LE(out,arg3[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusPokeStream(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,22);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  const int8* arg3 = ReadArrayInt8LE(in);
  ob->PokeStream(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusRefresh(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,23);
  ob->Refresh(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusCommit(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,24);
  int32 arg1 = ReadInt32LE(in);
  ob->Commit(ob,arg1);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitToggle8(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,25);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->BitToggle8(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitToggle16(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,26);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->BitToggle16(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitToggle32(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,27);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->BitToggle32(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusAssign8X(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,28);
  uint8 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  int32 arg4 = ReadInt32LE(in);
  ret = ob->Assign8X(ob,arg1,arg2,arg3,arg4);
  WriteInt8LE(out,0x00);
  WriteUInt8LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusAssign16X(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,29);
  uint16 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  int32 arg4 = ReadInt32LE(in);
  ret = ob->Assign16X(ob,arg1,arg2,arg3,arg4);
  WriteInt8LE(out,0x01);
  WriteUInt16LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusAssign32X(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,30);
  uint32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  int32 arg4 = ReadInt32LE(in);
  ret = ob->Assign32X(ob,arg1,arg2,arg3,arg4);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitsGet8(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,31);
  uint8 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  ret = ob->BitsGet8(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x00);
  WriteUInt8LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitsGet16(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,32);
  uint16 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  ret = ob->BitsGet16(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x01);
  WriteUInt16LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlBusBitsGet32(Bus *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,1);
  WriteInt8LE(out,33);
  uint32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  ret = ob->BitsGet32(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlBus,ARR((void *)tsctlBusLock,(void *)tsctlBusUnlock,(void *)tsctlBusPreempt,(void *)tsctlBusPeek8,(void *)tsctlBusPoke8,(void *)tsctlBusPeek16,(void *)tsctlBusPoke16,(void *)tsctlBusPeek32,(void *)tsctlBusPoke32,(void *)tsctlBusBitGet8,(void *)tsctlBusBitAssign8,(void *)tsctlBusBitSet8,(void *)tsctlBusBitClear8,(void *)tsctlBusBitGet16,(void *)tsctlBusBitAssign16,(void *)tsctlBusBitSet16,(void *)tsctlBusBitClear16,(void *)tsctlBusBitGet32,(void *)tsctlBusBitAssign32,(void *)tsctlBusBitSet32,(void *)tsctlBusBitClear32,(void *)tsctlBusPeekStream,(void *)tsctlBusPokeStream,(void *)tsctlBusRefresh,(void *)tsctlBusCommit,(void *)tsctlBusBitToggle8,(void *)tsctlBusBitToggle16,(void *)tsctlBusBitToggle32,(void *)tsctlBusAssign8X,(void *)tsctlBusAssign16X,(void *)tsctlBusAssign32X,(void *)tsctlBusBitsGet8,(void *)tsctlBusBitsGet16,(void *)tsctlBusBitsGet32,));

int tsctlTimeWait(Time *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,2);
  WriteInt8LE(out,0);
  uint32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  ret = ob->Wait(ob,arg1);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTimeDelay(Time *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,2);
  WriteInt8LE(out,1);
  uint32 arg1 = ReadUInt32LE(in);
  ob->Delay(ob,arg1);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTimeTick(Time *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,2);
  WriteInt8LE(out,2);
  uint32 ret;
  ret = ob->Tick(ob);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTimeusElapsed(Time *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,2);
  WriteInt8LE(out,3);
  uint32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  ret = ob->usElapsed(ob,arg1);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTimeusFuture(Time *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,2);
  WriteInt8LE(out,4);
  uint32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  uint32 arg2 = ReadUInt32LE(in);
  ret = ob->usFuture(ob,arg1,arg2);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTimeTimeoutQ(Time *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,2);
  WriteInt8LE(out,5);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  uint32 arg2 = ReadUInt32LE(in);
  ret = ob->TimeoutQ(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTimeTPS(Time *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,2);
  WriteInt8LE(out,6);
  uint32 ret;
  ret = ob->TPS(ob);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlTime,ARR((void *)tsctlTimeWait,(void *)tsctlTimeDelay,(void *)tsctlTimeTick,(void *)tsctlTimeusElapsed,(void *)tsctlTimeusFuture,(void *)tsctlTimeTimeoutQ,(void *)tsctlTimeTPS,));

int tsctlPinLock(Pin *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,3);
  WriteInt8LE(out,0);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Lock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlPinUnlock(Pin *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,3);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Unlock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlPinPreempt(Pin *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,3);
  WriteInt8LE(out,2);
  int32 ret;
  ret = ob->Preempt(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlPinModeGet(Pin *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,3);
  WriteInt8LE(out,3);
  Int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->ModeGet(ob,arg1);
  WriteInt8LE(out,0xC0);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlPinModeSet(Pin *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,3);
  WriteInt8LE(out,4);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  Int32 arg2 = ReadInt32LE(in);
  ret = ob->ModeSet(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlPin,ARR((void *)tsctlPinLock,(void *)tsctlPinUnlock,(void *)tsctlPinPreempt,(void *)tsctlPinModeGet,(void *)tsctlPinModeSet,));

int tsctlDIORawLock(DIORaw *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,4);
  WriteInt8LE(out,0);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Lock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIORawUnlock(DIORaw *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,4);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Unlock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIORawPreempt(DIORaw *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,4);
  WriteInt8LE(out,2);
  int32 ret;
  ret = ob->Preempt(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIORawDirSet(DIORaw *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,4);
  WriteInt8LE(out,3);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ob->DirSet(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIORawDataSet(DIORaw *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,4);
  WriteInt8LE(out,4);
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ob->DataSet(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIORawDirGet(DIORaw *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,4);
  WriteInt8LE(out,5);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->DirGet(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIORawDataGet(DIORaw *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,4);
  WriteInt8LE(out,6);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->DataGet(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIORawCount(DIORaw *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,4);
  WriteInt8LE(out,7);
  uint32 ret;
  ret = ob->Count(ob);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlDIORaw,ARR((void *)tsctlDIORawLock,(void *)tsctlDIORawUnlock,(void *)tsctlDIORawPreempt,(void *)tsctlDIORawDirSet,(void *)tsctlDIORawDataSet,(void *)tsctlDIORawDirGet,(void *)tsctlDIORawDataGet,(void *)tsctlDIORawCount,));

int tsctlDIOLock(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,0);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Lock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOUnlock(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Unlock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOPreempt(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,2);
  int32 ret;
  ret = ob->Preempt(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIORefresh(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,3);
  ob->Refresh(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOCommit(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,4);
  int32 arg1 = ReadInt32LE(in);
  ob->Commit(ob,arg1);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOSet(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,5);
  int32 arg1 = ReadInt32LE(in);
  Int32 arg2 = ReadInt32LE(in);
  ob->Set(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOGet(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,6);
  Int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->Get(ob,arg1);
  WriteInt8LE(out,0xC2);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOSetAsync(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,7);
  int32 arg1 = ReadInt32LE(in);
  Int32 arg2 = ReadInt32LE(in);
  ob->SetAsync(ob,arg1,arg2);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOGetAsync(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,8);
  Int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->GetAsync(ob,arg1);
  WriteInt8LE(out,0xC2);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOWait(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,9);
  int len1 = ReadInt32LE(in);
  int32* arg1 = ArrayAlloc(len1,sizeof(int32));
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  const int32* arg4 = ReadArrayInt32LE(in);
  const int32* arg5 = ReadArrayInt32LE(in);
  ob->Wait(ob,arg1,arg2,arg3,arg4,arg5);
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,ArrayLength(arg1));
  {
    int i;
    for(i=0;i<ArrayLength(arg1);i++) {
      WriteInt32LE(out,arg1[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOCount(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,10);
  uint32 ret;
  ret = ob->Count(ob);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOCapabilities(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,11);
  Int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  ret = ob->Capabilities(ob,arg1);
  WriteInt8LE(out,0xC3);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlDIOGetMulti(DIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,5);
  WriteInt8LE(out,12);
  int32 ret;
  int len1 = ReadInt32LE(in);
  int8* arg1 = ArrayAlloc(len1,sizeof(int8));
  int32 arg2 = ReadInt32LE(in);
  ret = ob->GetMulti(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x50);
  WriteInt32LE(out,ArrayLength(arg1));
  {
    int i;
    for(i=0;i<ArrayLength(arg1);i++) {
      WriteInt8LE(out,arg1[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlDIO,ARR((void *)tsctlDIOLock,(void *)tsctlDIOUnlock,(void *)tsctlDIOPreempt,(void *)tsctlDIORefresh,(void *)tsctlDIOCommit,(void *)tsctlDIOSet,(void *)tsctlDIOGet,(void *)tsctlDIOSetAsync,(void *)tsctlDIOGetAsync,(void *)tsctlDIOWait,(void *)tsctlDIOCount,(void *)tsctlDIOCapabilities,(void *)tsctlDIOGetMulti,));

int tsctlTWILock(TWI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,6);
  WriteInt8LE(out,0);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Lock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTWIUnlock(TWI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,6);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Unlock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTWIPreempt(TWI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,6);
  WriteInt8LE(out,2);
  int32 ret;
  ret = ob->Preempt(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTWIWrite(TWI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,6);
  WriteInt8LE(out,3);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  const int8* arg4 = ReadArrayInt8LE(in);
  ret = ob->Write(ob,arg1,arg2,arg3,arg4);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlTWIRead(TWI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,6);
  WriteInt8LE(out,4);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  int32 arg3 = ReadInt32LE(in);
  int len4 = ReadInt32LE(in);
  int8* arg4 = ArrayAlloc(len4,sizeof(int8));
  ret = ob->Read(ob,arg1,arg2,arg3,arg4);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x50);
  WriteInt32LE(out,ArrayLength(arg4));
  {
    int i;
    for(i=0;i<ArrayLength(arg4);i++) {
      WriteInt8LE(out,arg4[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlTWI,ARR((void *)tsctlTWILock,(void *)tsctlTWIUnlock,(void *)tsctlTWIPreempt,(void *)tsctlTWIWrite,(void *)tsctlTWIRead,));

int tsctlCANRx(CAN *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,7);
  WriteInt8LE(out,0);
  int32 ret;
  CANMessage arg1[1];
  ret = ob->Rx(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x74);
  WriteInt32LE(out,1);
  {
    int i;
    for(i=0;i<1;i++) {
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].flags);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].id);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].t_sec);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].t_usec);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].length);
      WriteInt8LE(out,0x40);
      WriteInt32LE(out,8);
      {
        int k;
        for(k=0;k<8;k++) {
          WriteUInt8LE(out,arg1[i].data[k]);
        }
      }
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlCANTx(CAN *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,7);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  uint32 arg2 = ReadUInt32LE(in);
  const int8* arg3 = ReadArrayInt8LE(in);
  ret = ob->Tx(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlCANBaudSet(CAN *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,7);
  WriteInt8LE(out,2);
  uint32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  ret = ob->BaudSet(ob,arg1);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlCANBaudGet(CAN *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,7);
  WriteInt8LE(out,3);
  uint32 ret;
  ret = ob->BaudGet(ob);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlCANAbort(CAN *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,7);
  WriteInt8LE(out,4);
  ob->Abort(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlCANRxMulti(CAN *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,7);
  WriteInt8LE(out,5);
  int32 ret;
  int len1 = ReadInt32LE(in);
  CANMessage* arg1 = ArrayAlloc(len1,sizeof(CANMessage));
  int32 arg2 = ReadInt32LE(in);
  ret = ob->RxMulti(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x74);
  WriteInt32LE(out,ArrayLength(arg1));
  {
    int i;
    for(i=0;i<ArrayLength(arg1);i++) {
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].flags);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].id);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].t_sec);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].t_usec);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,arg1[i].length);
      WriteInt8LE(out,0x40);
      WriteInt32LE(out,8);
      {
        int k;
        for(k=0;k<8;k++) {
          WriteUInt8LE(out,arg1[i].data[k]);
        }
      }
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlCAN,ARR((void *)tsctlCANRx,(void *)tsctlCANTx,(void *)tsctlCANBaudSet,(void *)tsctlCANBaudGet,(void *)tsctlCANAbort,(void *)tsctlCANRxMulti,));

int tsctlSPILock(SPI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,8);
  WriteInt8LE(out,0);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Lock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSPIUnlock(SPI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,8);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Unlock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSPIPreempt(SPI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,8);
  WriteInt8LE(out,2);
  int32 ret;
  ret = ob->Preempt(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSPIWrite(SPI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,8);
  WriteInt8LE(out,3);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  const uint8* arg2 = ReadArrayUInt8LE(in);
  ret = ob->Write(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSPIRead(SPI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,8);
  WriteInt8LE(out,4);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int len2 = ReadInt32LE(in);
  uint8* arg2 = ArrayAlloc(len2,sizeof(uint8));
  ret = ob->Read(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x40);
  WriteInt32LE(out,ArrayLength(arg2));
  {
    int i;
    for(i=0;i<ArrayLength(arg2);i++) {
      WriteUInt8LE(out,arg2[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSPIReadWrite(SPI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,8);
  WriteInt8LE(out,5);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  const uint8* arg2 = ReadArrayUInt8LE(in);
  int len3 = ReadInt32LE(in);
  uint8* arg3 = ArrayAlloc(len3,sizeof(uint8));
  ret = ob->ReadWrite(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x40);
  WriteInt32LE(out,ArrayLength(arg3));
  {
    int i;
    for(i=0;i<ArrayLength(arg3);i++) {
      WriteUInt8LE(out,arg3[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSPIClockSet(SPI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,8);
  WriteInt8LE(out,6);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  ret = ob->ClockSet(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlSPIEdgeSet(SPI *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,8);
  WriteInt8LE(out,7);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->EdgeSet(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlSPI,ARR((void *)tsctlSPILock,(void *)tsctlSPIUnlock,(void *)tsctlSPIPreempt,(void *)tsctlSPIWrite,(void *)tsctlSPIRead,(void *)tsctlSPIReadWrite,(void *)tsctlSPIClockSet,(void *)tsctlSPIEdgeSet,));

int tsctlAIOLock(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,0);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Lock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOUnlock(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Unlock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOPreempt(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,2);
  int32 ret;
  ret = ob->Preempt(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOType(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,3);
  Int32 ret;
  ret = ob->Type(ob);
  WriteInt8LE(out,0xC9);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOVoltageRangeList(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,4);
  VoltageRange* ret;
  ret = ob->VoltageRangeList(ob);
  WriteInt8LE(out,0x70);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt8LE(out,0x31);
        WriteInt8LE(out,0x23);
        WriteReal32LE(out,ret[i].low.start);
        WriteInt8LE(out,0x23);
        WriteReal32LE(out,ret[i].low.step);
        WriteInt8LE(out,0x03);
        WriteUInt32LE(out,ret[i].low.count);
      WriteInt8LE(out,0x31);
        WriteInt8LE(out,0x23);
        WriteReal32LE(out,ret[i].high.start);
        WriteInt8LE(out,0x23);
        WriteReal32LE(out,ret[i].high.step);
        WriteInt8LE(out,0x03);
        WriteUInt32LE(out,ret[i].high.count);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOPrecisionList(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,5);
  int32 ret;
  ret = ob->PrecisionList(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOPeriodRangeList(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,6);
  PeriodRange* ret;
  ret = ob->PeriodRangeList(ob);
  WriteInt8LE(out,0x71);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,ret[i].start);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,ret[i].step);
      WriteInt8LE(out,0x03);
      WriteUInt32LE(out,ret[i].count);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOTriggerList(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,7);
  int32* ret;
  ret = ob->TriggerList(ob);
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt32LE(out,ret[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOChannels(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,8);
  int32 ret;
  ret = ob->Channels(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOReset(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,9);
  ob->Reset(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOChannelEnable(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,10);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->ChannelEnable(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOChannelSamplePeriod(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,11);
  uint32 ret;
  int32 arg1 = ReadInt32LE(in);
  uint32 arg2 = ReadUInt32LE(in);
  ret = ob->ChannelSamplePeriod(ob,arg1,arg2);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOChannelPrecision(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,12);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->ChannelPrecision(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOChannelVoltageRange(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,13);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  real32 arg2 = ReadReal32LE(in);
  real32 arg3 = ReadReal32LE(in);
  ret = ob->ChannelVoltageRange(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOConfiguration(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,14);
  int32 ret;
  int len1 = ReadInt32LE(in);
  real32* arg1 = ArrayAlloc(len1,sizeof(real32));
  int len2 = ReadInt32LE(in);
  real32* arg2 = ArrayAlloc(len2,sizeof(real32));
  int len3 = ReadInt32LE(in);
  int32* arg3 = ArrayAlloc(len3,sizeof(int32));
  int len4 = ReadInt32LE(in);
  int32* arg4 = ArrayAlloc(len4,sizeof(int32));
  int len5 = ReadInt32LE(in);
  int32* arg5 = ArrayAlloc(len5,sizeof(int32));
  int32 arg6[1];
  ret = ob->Configuration(ob,arg1,arg2,arg3,arg4,arg5,arg6);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x63);
  WriteInt32LE(out,ArrayLength(arg1));
  {
    int i;
    for(i=0;i<ArrayLength(arg1);i++) {
      WriteReal32LE(out,arg1[i]);
    }
  }
  WriteInt8LE(out,0x63);
  WriteInt32LE(out,ArrayLength(arg2));
  {
    int i;
    for(i=0;i<ArrayLength(arg2);i++) {
      WriteReal32LE(out,arg2[i]);
    }
  }
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,ArrayLength(arg3));
  {
    int i;
    for(i=0;i<ArrayLength(arg3);i++) {
      WriteInt32LE(out,arg3[i]);
    }
  }
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,ArrayLength(arg4));
  {
    int i;
    for(i=0;i<ArrayLength(arg4);i++) {
      WriteInt32LE(out,arg4[i]);
    }
  }
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,ArrayLength(arg5));
  {
    int i;
    for(i=0;i<ArrayLength(arg5);i++) {
      WriteInt32LE(out,arg5[i]);
    }
  }
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,1);
  {
    int i;
    for(i=0;i<1;i++) {
      WriteInt32LE(out,arg6[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOConfigureTest(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,15);
  int32 ret;
  const real32* arg1 = ReadArrayReal32LE(in);
  const real32* arg2 = ReadArrayReal32LE(in);
  const int32* arg3 = ReadArrayInt32LE(in);
  const int32* arg4 = ReadArrayInt32LE(in);
  const int32* arg5 = ReadArrayInt32LE(in);
  int32 arg6 = ReadInt32LE(in);
  ret = ob->ConfigureTest(ob,arg1,arg2,arg3,arg4,arg5,arg6);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOConfigure(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,16);
  int32 ret;
  const real32* arg1 = ReadArrayReal32LE(in);
  const real32* arg2 = ReadArrayReal32LE(in);
  const int32* arg3 = ReadArrayInt32LE(in);
  const int32* arg4 = ReadArrayInt32LE(in);
  const int32* arg5 = ReadArrayInt32LE(in);
  int32 arg6 = ReadInt32LE(in);
  ret = ob->Configure(ob,arg1,arg2,arg3,arg4,arg5,arg6);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOITrig(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,17);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->ITrig(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOGet(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,18);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->Get(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOPut(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,19);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Put(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOReady(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,20);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->Ready(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOGets8(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,21);
  int32 ret;
  int len1 = ReadInt32LE(in);
  int8* arg1 = ArrayAlloc(len1,sizeof(int8));
  ret = ob->Gets8(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x50);
  WriteInt32LE(out,ArrayLength(arg1));
  {
    int i;
    for(i=0;i<ArrayLength(arg1);i++) {
      WriteInt8LE(out,arg1[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOGets16(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,22);
  int32 ret;
  int len1 = ReadInt32LE(in);
  int16* arg1 = ArrayAlloc(len1,sizeof(int16));
  ret = ob->Gets16(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x51);
  WriteInt32LE(out,ArrayLength(arg1));
  {
    int i;
    for(i=0;i<ArrayLength(arg1);i++) {
      WriteInt16LE(out,arg1[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOGets32(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,23);
  int32 ret;
  int len1 = ReadInt32LE(in);
  int32* arg1 = ArrayAlloc(len1,sizeof(int32));
  ret = ob->Gets32(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,ArrayLength(arg1));
  {
    int i;
    for(i=0;i<ArrayLength(arg1);i++) {
      WriteInt32LE(out,arg1[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOPuts8(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,24);
  int32 ret;
  const int8* arg1 = ReadArrayInt8LE(in);
  ret = ob->Puts8(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOPuts16(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,25);
  int32 ret;
  const int16* arg1 = ReadArrayInt16LE(in);
  ret = ob->Puts16(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOPuts32(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,26);
  int32 ret;
  const int32* arg1 = ReadArrayInt32LE(in);
  ret = ob->Puts32(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOReadys8(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,27);
  int32 ret;
  const int8* arg1 = ReadArrayInt8LE(in);
  ret = ob->Readys8(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOReadys16(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,28);
  int32 ret;
  const int16* arg1 = ReadArrayInt16LE(in);
  ret = ob->Readys16(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlAIOReadys32(AIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,9);
  WriteInt8LE(out,29);
  int32 ret;
  const int32* arg1 = ReadArrayInt32LE(in);
  ret = ob->Readys32(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlAIO,ARR((void *)tsctlAIOLock,(void *)tsctlAIOUnlock,(void *)tsctlAIOPreempt,(void *)tsctlAIOType,(void *)tsctlAIOVoltageRangeList,(void *)tsctlAIOPrecisionList,(void *)tsctlAIOPeriodRangeList,(void *)tsctlAIOTriggerList,(void *)tsctlAIOChannels,(void *)tsctlAIOReset,(void *)tsctlAIOChannelEnable,(void *)tsctlAIOChannelSamplePeriod,(void *)tsctlAIOChannelPrecision,(void *)tsctlAIOChannelVoltageRange,(void *)tsctlAIOConfiguration,(void *)tsctlAIOConfigureTest,(void *)tsctlAIOConfigure,(void *)tsctlAIOITrig,(void *)tsctlAIOGet,(void *)tsctlAIOPut,(void *)tsctlAIOReady,(void *)tsctlAIOGets8,(void *)tsctlAIOGets16,(void *)tsctlAIOGets32,(void *)tsctlAIOPuts8,(void *)tsctlAIOPuts16,(void *)tsctlAIOPuts32,(void *)tsctlAIOReadys8,(void *)tsctlAIOReadys16,(void *)tsctlAIOReadys32,));

int tsctlEDIOLock(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,0);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Lock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOUnlock(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,1);
  int32 ret;
  uint32 arg1 = ReadUInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->Unlock(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOPreempt(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,2);
  int32 ret;
  ret = ob->Preempt(ob);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOQueryFunction(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,3);
  int32* ret;
  Int32 arg1 = ReadInt32LE(in);
  ret = ob->QueryFunction(ob,arg1);
  WriteInt8LE(out,0x53);
  WriteInt32LE(out,ArrayLength(ret));
  {
    int i;
    for(i=0;i<ArrayLength(ret);i++) {
      WriteInt32LE(out,ret[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOPWM(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,4);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  uint32 arg2 = ReadUInt32LE(in);
  uint32 arg3 = ReadUInt32LE(in);
  ret = ob->PWM(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOQueryPWM(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,5);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  uint32 arg2[1];
  uint32 arg3[1];
  ret = ob->QueryPWM(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x43);
  WriteInt32LE(out,1);
  {
    int i;
    for(i=0;i<1;i++) {
      WriteUInt32LE(out,arg2[i]);
    }
  }
  WriteInt8LE(out,0x43);
  WriteInt32LE(out,1);
  {
    int i;
    for(i=0;i<1;i++) {
      WriteUInt32LE(out,arg3[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOPWMfd(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,6);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  uint32 arg2 = ReadUInt32LE(in);
  uint32 arg3 = ReadUInt32LE(in);
  ret = ob->PWMfd(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOQueryPWMfd(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,7);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  uint32 arg2[1];
  uint32 arg3[1];
  ret = ob->QueryPWMfd(ob,arg1,arg2,arg3);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x43);
  WriteInt32LE(out,1);
  {
    int i;
    for(i=0;i<1;i++) {
      WriteUInt32LE(out,arg2[i]);
    }
  }
  WriteInt8LE(out,0x43);
  WriteInt32LE(out,1);
  {
    int i;
    for(i=0;i<1;i++) {
      WriteUInt32LE(out,arg3[i]);
    }
  }
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOQuadratureCount(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,8);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->QuadratureCount(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOEdgeCount(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,9);
  uint32 ret;
  int32 arg1 = ReadInt32LE(in);
  int32 arg2 = ReadInt32LE(in);
  ret = ob->EdgeCount(ob,arg1,arg2);
  WriteInt8LE(out,0x03);
  WriteUInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOGlitched(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,10);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  ret = ob->Glitched(ob,arg1);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlEDIOHBridge(EDIO *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,10);
  WriteInt8LE(out,11);
  int32 ret;
  int32 arg1 = ReadInt32LE(in);
  Int32 arg2 = ReadInt32LE(in);
  ret = ob->HBridge(ob,arg1,arg2);
  WriteInt8LE(out,0x13);
  WriteInt32LE(out,ret);
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlEDIO,ARR((void *)tsctlEDIOLock,(void *)tsctlEDIOUnlock,(void *)tsctlEDIOPreempt,(void *)tsctlEDIOQueryFunction,(void *)tsctlEDIOPWM,(void *)tsctlEDIOQueryPWM,(void *)tsctlEDIOPWMfd,(void *)tsctlEDIOQueryPWMfd,(void *)tsctlEDIOQuadratureCount,(void *)tsctlEDIOEdgeCount,(void *)tsctlEDIOGlitched,(void *)tsctlEDIOHBridge,));

int tsctlModeJSON(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,0);
  ob->JSON(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeAssign(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,1);
  ob->Assign(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeNoAssign(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,2);
  ob->NoAssign(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeHex(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,3);
  ob->Hex(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeDec(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,4);
  ob->Dec(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeOct(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,5);
  ob->Oct(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeAStr(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,6);
  ob->AStr(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeAHex(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,7);
  ob->AHex(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeADec(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,8);
  ob->ADec(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeAOct(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,9);
  ob->AOct(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeABinOct(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,10);
  ob->ABinOct(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeABinHex(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,11);
  ob->ABinHex(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
int tsctlModeABinUni(Mode *ob,Stream *out,Stream *in) {
  WriteInt16LE(out,11);
  WriteInt8LE(out,12);
  ob->ABinUni(ob);
  WriteInt8LE(out,0x80);
  return 1;
}
ArrayAuto(void **,tsctlMode,ARR((void *)tsctlModeJSON,(void *)tsctlModeAssign,(void *)tsctlModeNoAssign,(void *)tsctlModeHex,(void *)tsctlModeDec,(void *)tsctlModeOct,(void *)tsctlModeAStr,(void *)tsctlModeAHex,(void *)tsctlModeADec,(void *)tsctlModeAOct,(void *)tsctlModeABinOct,(void *)tsctlModeABinHex,(void *)tsctlModeABinUni,));

ArrayAuto(void***,docmd,ARR(ArrayL(tsctlSystem),ArrayL(tsctlBus),ArrayL(tsctlTime),ArrayL(tsctlPin),ArrayL(tsctlDIORaw),ArrayL(tsctlDIO),ArrayL(tsctlTWI),ArrayL(tsctlCAN),ArrayL(tsctlSPI),ArrayL(tsctlAIO),ArrayL(tsctlEDIO),ArrayL(tsctlMode),));

ArrayAuto(char*,SystemCmdName,ARR("ClassCount","InstanceCount","APICount","LockCount","LockHolderInfo","ConnWaitInfo","CANBusGet","BuildInfo","ModelId","BaseBoardId","MapLength","MapGet","MapLookup","MapLookupPartial","MapAdd","MapDelete","Note",));
ArrayAuto(char*,BusCmdName,ARR("Lock","Unlock","Preempt","Peek8","Poke8","Peek16","Poke16","Peek32","Poke32","BitGet8","BitAssign8","BitSet8","BitClear8","BitGet16","BitAssign16","BitSet16","BitClear16","BitGet32","BitAssign32","BitSet32","BitClear32","PeekStream","PokeStream","Refresh","Commit","BitToggle8","BitToggle16","BitToggle32","Assign8X","Assign16X","Assign32X","BitsGet8","BitsGet16","BitsGet32",));
ArrayAuto(char*,TimeCmdName,ARR("Wait","Delay","Tick","usElapsed","usFuture","TimeoutQ","TPS",));
ArrayAuto(char*,PinCmdName,ARR("Lock","Unlock","Preempt","ModeGet","ModeSet",));
ArrayAuto(char*,DIORawCmdName,ARR("Lock","Unlock","Preempt","DirSet","DataSet","DirGet","DataGet","Count",));
ArrayAuto(char*,DIOCmdName,ARR("Lock","Unlock","Preempt","Refresh","Commit","Set","Get","SetAsync","GetAsync","Wait","Count","Capabilities","GetMulti",));
ArrayAuto(char*,TWICmdName,ARR("Lock","Unlock","Preempt","Write","Read",));
ArrayAuto(char*,CANCmdName,ARR("Rx","Tx","BaudSet","BaudGet","Abort","RxMulti",));
ArrayAuto(char*,SPICmdName,ARR("Lock","Unlock","Preempt","Write","Read","ReadWrite","ClockSet","EdgeSet",));
ArrayAuto(char*,AIOCmdName,ARR("Lock","Unlock","Preempt","Type","VoltageRangeList","PrecisionList","PeriodRangeList","TriggerList","Channels","Reset","ChannelEnable","ChannelSamplePeriod","ChannelPrecision","ChannelVoltageRange","Configuration","ConfigureTest","Configure","ITrig","Get","Put","Ready","Gets8","Gets16","Gets32","Puts8","Puts16","Puts32","Readys8","Readys16","Readys32",));
ArrayAuto(char*,EDIOCmdName,ARR("Lock","Unlock","Preempt","QueryFunction","PWM","QueryPWM","PWMfd","QueryPWMfd","QuadratureCount","EdgeCount","Glitched","HBridge",));
ArrayAuto(char*,ModeCmdName,ARR("JSON","Assign","NoAssign","Hex","Dec","Oct","AStr","AHex","ADec","AOct","ABinOct","ABinHex","ABinUni",));

ArrayAuto(char**,cmdname,ARR(ArrayL(SystemCmdName),ArrayL(BusCmdName),ArrayL(TimeCmdName),ArrayL(PinCmdName),ArrayL(DIORawCmdName),ArrayL(DIOCmdName),ArrayL(TWICmdName),ArrayL(CANCmdName),ArrayL(SPICmdName),ArrayL(AIOCmdName),ArrayL(EDIOCmdName),ArrayL(ModeCmdName),));

ArrayAuto(char*,classname,ARR("System","Bus","Time","Pin","DIORaw","DIO","TWI","CAN","SPI","AIO","EDIO","Mode",));
// =================================
ArrayAuto(char*,SystemClassCountRetNames,ARR("",));
ArrayAuto(char*,SystemInstanceCountRetNames,ARR("",));
ArrayAuto(char*,SystemAPICountRetNames,ARR("",));
ArrayAuto(char*,SystemLockCountRetNames,ARR("",));
ArrayAuto(char*,SystemLockHolderInfoRetNames,ARR("pid","count",));
ArrayAuto(char*,SystemConnWaitInfoRetNames,ARR("pid","wait",));
ArrayAuto(char*,SystemCANBusGetRetNames,ARR("",));
ArrayAuto(char*,SystemBuildInfoRetNames,ARR("","info_%d_buildNumber","info_%d_buildTime","info_%d_uptime","info_%d_hostname","info_%d_hostname","info_%d_arch","info_%d_arch",));
ArrayAuto(char*,SystemModelIdRetNames,ARR("",));
ArrayAuto(char*,SystemBaseBoardIdRetNames,ARR("",));
ArrayAuto(char*,SystemMapLengthRetNames,ARR("",));
ArrayAuto(char*,SystemMapGetRetNames,ARR("","Value",));
ArrayAuto(char*,SystemMapLookupRetNames,ARR("",));
ArrayAuto(char*,SystemMapLookupPartialRetNames,ARR("",));
ArrayAuto(char*,SystemMapAddRetNames,ARR("",));
ArrayAuto(char*,SystemMapDeleteRetNames,ARR("",));
ArrayAuto(char*,SystemNoteRetNames,ARR("",));
ArrayAuto(char**,SystemRetNames,ARR(ArrayL(SystemClassCountRetNames),ArrayL(SystemInstanceCountRetNames),ArrayL(SystemAPICountRetNames),ArrayL(SystemLockCountRetNames),ArrayL(SystemLockHolderInfoRetNames),ArrayL(SystemConnWaitInfoRetNames),ArrayL(SystemCANBusGetRetNames),ArrayL(SystemBuildInfoRetNames),ArrayL(SystemModelIdRetNames),ArrayL(SystemBaseBoardIdRetNames),ArrayL(SystemMapLengthRetNames),ArrayL(SystemMapGetRetNames),ArrayL(SystemMapLookupRetNames),ArrayL(SystemMapLookupPartialRetNames),ArrayL(SystemMapAddRetNames),ArrayL(SystemMapDeleteRetNames),ArrayL(SystemNoteRetNames),));

ArrayAuto(char*,BusLockRetNames,ARR("",));
ArrayAuto(char*,BusUnlockRetNames,ARR("",));
ArrayAuto(char*,BusPreemptRetNames,ARR("",));
ArrayAuto(char*,BusPeek8RetNames,ARR("",));
ArrayAuto(char*,BusPoke8RetNames,ARR("",));
ArrayAuto(char*,BusPeek16RetNames,ARR("",));
ArrayAuto(char*,BusPoke16RetNames,ARR("",));
ArrayAuto(char*,BusPeek32RetNames,ARR("",));
ArrayAuto(char*,BusPoke32RetNames,ARR("",));
ArrayAuto(char*,BusBitGet8RetNames,ARR("",));
ArrayAuto(char*,BusBitAssign8RetNames,ARR("",));
ArrayAuto(char*,BusBitSet8RetNames,ARR("",));
ArrayAuto(char*,BusBitClear8RetNames,ARR("",));
ArrayAuto(char*,BusBitGet16RetNames,ARR("",));
ArrayAuto(char*,BusBitAssign16RetNames,ARR("",));
ArrayAuto(char*,BusBitSet16RetNames,ARR("",));
ArrayAuto(char*,BusBitClear16RetNames,ARR("",));
ArrayAuto(char*,BusBitGet32RetNames,ARR("",));
ArrayAuto(char*,BusBitAssign32RetNames,ARR("",));
ArrayAuto(char*,BusBitSet32RetNames,ARR("",));
ArrayAuto(char*,BusBitClear32RetNames,ARR("",));
ArrayAuto(char*,BusPeekStreamRetNames,ARR("","dest",));
ArrayAuto(char*,BusPokeStreamRetNames,ARR("",));
ArrayAuto(char*,BusRefreshRetNames,ARR("",));
ArrayAuto(char*,BusCommitRetNames,ARR("",));
ArrayAuto(char*,BusBitToggle8RetNames,ARR("",));
ArrayAuto(char*,BusBitToggle16RetNames,ARR("",));
ArrayAuto(char*,BusBitToggle32RetNames,ARR("",));
ArrayAuto(char*,BusAssign8XRetNames,ARR("",));
ArrayAuto(char*,BusAssign16XRetNames,ARR("",));
ArrayAuto(char*,BusAssign32XRetNames,ARR("",));
ArrayAuto(char*,BusBitsGet8RetNames,ARR("",));
ArrayAuto(char*,BusBitsGet16RetNames,ARR("",));
ArrayAuto(char*,BusBitsGet32RetNames,ARR("",));
ArrayAuto(char**,BusRetNames,ARR(ArrayL(BusLockRetNames),ArrayL(BusUnlockRetNames),ArrayL(BusPreemptRetNames),ArrayL(BusPeek8RetNames),ArrayL(BusPoke8RetNames),ArrayL(BusPeek16RetNames),ArrayL(BusPoke16RetNames),ArrayL(BusPeek32RetNames),ArrayL(BusPoke32RetNames),ArrayL(BusBitGet8RetNames),ArrayL(BusBitAssign8RetNames),ArrayL(BusBitSet8RetNames),ArrayL(BusBitClear8RetNames),ArrayL(BusBitGet16RetNames),ArrayL(BusBitAssign16RetNames),ArrayL(BusBitSet16RetNames),ArrayL(BusBitClear16RetNames),ArrayL(BusBitGet32RetNames),ArrayL(BusBitAssign32RetNames),ArrayL(BusBitSet32RetNames),ArrayL(BusBitClear32RetNames),ArrayL(BusPeekStreamRetNames),ArrayL(BusPokeStreamRetNames),ArrayL(BusRefreshRetNames),ArrayL(BusCommitRetNames),ArrayL(BusBitToggle8RetNames),ArrayL(BusBitToggle16RetNames),ArrayL(BusBitToggle32RetNames),ArrayL(BusAssign8XRetNames),ArrayL(BusAssign16XRetNames),ArrayL(BusAssign32XRetNames),ArrayL(BusBitsGet8RetNames),ArrayL(BusBitsGet16RetNames),ArrayL(BusBitsGet32RetNames),));

ArrayAuto(char*,TimeWaitRetNames,ARR("",));
ArrayAuto(char*,TimeDelayRetNames,ARR("",));
ArrayAuto(char*,TimeTickRetNames,ARR("",));
ArrayAuto(char*,TimeusElapsedRetNames,ARR("",));
ArrayAuto(char*,TimeusFutureRetNames,ARR("",));
ArrayAuto(char*,TimeTimeoutQRetNames,ARR("",));
ArrayAuto(char*,TimeTPSRetNames,ARR("",));
ArrayAuto(char**,TimeRetNames,ARR(ArrayL(TimeWaitRetNames),ArrayL(TimeDelayRetNames),ArrayL(TimeTickRetNames),ArrayL(TimeusElapsedRetNames),ArrayL(TimeusFutureRetNames),ArrayL(TimeTimeoutQRetNames),ArrayL(TimeTPSRetNames),));

ArrayAuto(char*,PinLockRetNames,ARR("",));
ArrayAuto(char*,PinUnlockRetNames,ARR("",));
ArrayAuto(char*,PinPreemptRetNames,ARR("",));
ArrayAuto(char*,PinModeGetRetNames,ARR("",));
ArrayAuto(char*,PinModeSetRetNames,ARR("",));
ArrayAuto(char**,PinRetNames,ARR(ArrayL(PinLockRetNames),ArrayL(PinUnlockRetNames),ArrayL(PinPreemptRetNames),ArrayL(PinModeGetRetNames),ArrayL(PinModeSetRetNames),));

ArrayAuto(char*,DIORawLockRetNames,ARR("",));
ArrayAuto(char*,DIORawUnlockRetNames,ARR("",));
ArrayAuto(char*,DIORawPreemptRetNames,ARR("",));
ArrayAuto(char*,DIORawDirSetRetNames,ARR("",));
ArrayAuto(char*,DIORawDataSetRetNames,ARR("",));
ArrayAuto(char*,DIORawDirGetRetNames,ARR("",));
ArrayAuto(char*,DIORawDataGetRetNames,ARR("",));
ArrayAuto(char*,DIORawCountRetNames,ARR("",));
ArrayAuto(char**,DIORawRetNames,ARR(ArrayL(DIORawLockRetNames),ArrayL(DIORawUnlockRetNames),ArrayL(DIORawPreemptRetNames),ArrayL(DIORawDirSetRetNames),ArrayL(DIORawDataSetRetNames),ArrayL(DIORawDirGetRetNames),ArrayL(DIORawDataGetRetNames),ArrayL(DIORawCountRetNames),));

ArrayAuto(char*,DIOLockRetNames,ARR("",));
ArrayAuto(char*,DIOUnlockRetNames,ARR("",));
ArrayAuto(char*,DIOPreemptRetNames,ARR("",));
ArrayAuto(char*,DIORefreshRetNames,ARR("",));
ArrayAuto(char*,DIOCommitRetNames,ARR("",));
ArrayAuto(char*,DIOSetRetNames,ARR("",));
ArrayAuto(char*,DIOGetRetNames,ARR("",));
ArrayAuto(char*,DIOSetAsyncRetNames,ARR("",));
ArrayAuto(char*,DIOGetAsyncRetNames,ARR("",));
ArrayAuto(char*,DIOWaitRetNames,ARR("","match",));
ArrayAuto(char*,DIOCountRetNames,ARR("",));
ArrayAuto(char*,DIOCapabilitiesRetNames,ARR("",));
ArrayAuto(char*,DIOGetMultiRetNames,ARR("","state",));
ArrayAuto(char**,DIORetNames,ARR(ArrayL(DIOLockRetNames),ArrayL(DIOUnlockRetNames),ArrayL(DIOPreemptRetNames),ArrayL(DIORefreshRetNames),ArrayL(DIOCommitRetNames),ArrayL(DIOSetRetNames),ArrayL(DIOGetRetNames),ArrayL(DIOSetAsyncRetNames),ArrayL(DIOGetAsyncRetNames),ArrayL(DIOWaitRetNames),ArrayL(DIOCountRetNames),ArrayL(DIOCapabilitiesRetNames),ArrayL(DIOGetMultiRetNames),));

ArrayAuto(char*,TWILockRetNames,ARR("",));
ArrayAuto(char*,TWIUnlockRetNames,ARR("",));
ArrayAuto(char*,TWIPreemptRetNames,ARR("",));
ArrayAuto(char*,TWIWriteRetNames,ARR("",));
ArrayAuto(char*,TWIReadRetNames,ARR("","bytes",));
ArrayAuto(char**,TWIRetNames,ARR(ArrayL(TWILockRetNames),ArrayL(TWIUnlockRetNames),ArrayL(TWIPreemptRetNames),ArrayL(TWIWriteRetNames),ArrayL(TWIReadRetNames),));

ArrayAuto(char*,CANRxRetNames,ARR("","message_%d_flags","message_%d_id","message_%d_t_sec","message_%d_t_usec","message_%d_length","message_%d_data","message_%d_data",));
ArrayAuto(char*,CANTxRetNames,ARR("",));
ArrayAuto(char*,CANBaudSetRetNames,ARR("",));
ArrayAuto(char*,CANBaudGetRetNames,ARR("",));
ArrayAuto(char*,CANAbortRetNames,ARR("",));
ArrayAuto(char*,CANRxMultiRetNames,ARR("","msg_%d_flags","msg_%d_id","msg_%d_t_sec","msg_%d_t_usec","msg_%d_length","msg_%d_data","msg_%d_data",));
ArrayAuto(char**,CANRetNames,ARR(ArrayL(CANRxRetNames),ArrayL(CANTxRetNames),ArrayL(CANBaudSetRetNames),ArrayL(CANBaudGetRetNames),ArrayL(CANAbortRetNames),ArrayL(CANRxMultiRetNames),));

ArrayAuto(char*,SPILockRetNames,ARR("",));
ArrayAuto(char*,SPIUnlockRetNames,ARR("",));
ArrayAuto(char*,SPIPreemptRetNames,ARR("",));
ArrayAuto(char*,SPIWriteRetNames,ARR("",));
ArrayAuto(char*,SPIReadRetNames,ARR("","buf",));
ArrayAuto(char*,SPIReadWriteRetNames,ARR("","rbuf",));
ArrayAuto(char*,SPIClockSetRetNames,ARR("",));
ArrayAuto(char*,SPIEdgeSetRetNames,ARR("",));
ArrayAuto(char**,SPIRetNames,ARR(ArrayL(SPILockRetNames),ArrayL(SPIUnlockRetNames),ArrayL(SPIPreemptRetNames),ArrayL(SPIWriteRetNames),ArrayL(SPIReadRetNames),ArrayL(SPIReadWriteRetNames),ArrayL(SPIClockSetRetNames),ArrayL(SPIEdgeSetRetNames),));

ArrayAuto(char*,AIOLockRetNames,ARR("",));
ArrayAuto(char*,AIOUnlockRetNames,ARR("",));
ArrayAuto(char*,AIOPreemptRetNames,ARR("",));
ArrayAuto(char*,AIOTypeRetNames,ARR("",));
ArrayAuto(char*,AIOVoltageRangeListRetNames,ARR("low_start","low_step","low_count","high_start","high_step","high_count",));
ArrayAuto(char*,AIOPrecisionListRetNames,ARR("",));
ArrayAuto(char*,AIOPeriodRangeListRetNames,ARR("start","step","count",));
ArrayAuto(char*,AIOTriggerListRetNames,ARR("",));
ArrayAuto(char*,AIOChannelsRetNames,ARR("",));
ArrayAuto(char*,AIOResetRetNames,ARR("",));
ArrayAuto(char*,AIOChannelEnableRetNames,ARR("",));
ArrayAuto(char*,AIOChannelSamplePeriodRetNames,ARR("",));
ArrayAuto(char*,AIOChannelPrecisionRetNames,ARR("",));
ArrayAuto(char*,AIOChannelVoltageRangeRetNames,ARR("",));
ArrayAuto(char*,AIOConfigurationRetNames,ARR("","low","high","prec","t","trigger","itrig",));
ArrayAuto(char*,AIOConfigureTestRetNames,ARR("",));
ArrayAuto(char*,AIOConfigureRetNames,ARR("",));
ArrayAuto(char*,AIOITrigRetNames,ARR("",));
ArrayAuto(char*,AIOGetRetNames,ARR("",));
ArrayAuto(char*,AIOPutRetNames,ARR("",));
ArrayAuto(char*,AIOReadyRetNames,ARR("",));
ArrayAuto(char*,AIOGets8RetNames,ARR("","buf",));
ArrayAuto(char*,AIOGets16RetNames,ARR("","buf",));
ArrayAuto(char*,AIOGets32RetNames,ARR("","buf",));
ArrayAuto(char*,AIOPuts8RetNames,ARR("",));
ArrayAuto(char*,AIOPuts16RetNames,ARR("",));
ArrayAuto(char*,AIOPuts32RetNames,ARR("",));
ArrayAuto(char*,AIOReadys8RetNames,ARR("",));
ArrayAuto(char*,AIOReadys16RetNames,ARR("",));
ArrayAuto(char*,AIOReadys32RetNames,ARR("",));
ArrayAuto(char**,AIORetNames,ARR(ArrayL(AIOLockRetNames),ArrayL(AIOUnlockRetNames),ArrayL(AIOPreemptRetNames),ArrayL(AIOTypeRetNames),ArrayL(AIOVoltageRangeListRetNames),ArrayL(AIOPrecisionListRetNames),ArrayL(AIOPeriodRangeListRetNames),ArrayL(AIOTriggerListRetNames),ArrayL(AIOChannelsRetNames),ArrayL(AIOResetRetNames),ArrayL(AIOChannelEnableRetNames),ArrayL(AIOChannelSamplePeriodRetNames),ArrayL(AIOChannelPrecisionRetNames),ArrayL(AIOChannelVoltageRangeRetNames),ArrayL(AIOConfigurationRetNames),ArrayL(AIOConfigureTestRetNames),ArrayL(AIOConfigureRetNames),ArrayL(AIOITrigRetNames),ArrayL(AIOGetRetNames),ArrayL(AIOPutRetNames),ArrayL(AIOReadyRetNames),ArrayL(AIOGets8RetNames),ArrayL(AIOGets16RetNames),ArrayL(AIOGets32RetNames),ArrayL(AIOPuts8RetNames),ArrayL(AIOPuts16RetNames),ArrayL(AIOPuts32RetNames),ArrayL(AIOReadys8RetNames),ArrayL(AIOReadys16RetNames),ArrayL(AIOReadys32RetNames),));

ArrayAuto(char*,EDIOLockRetNames,ARR("",));
ArrayAuto(char*,EDIOUnlockRetNames,ARR("",));
ArrayAuto(char*,EDIOPreemptRetNames,ARR("",));
ArrayAuto(char*,EDIOQueryFunctionRetNames,ARR("",));
ArrayAuto(char*,EDIOPWMRetNames,ARR("",));
ArrayAuto(char*,EDIOQueryPWMRetNames,ARR("","periodHigh","periodLow",));
ArrayAuto(char*,EDIOPWMfdRetNames,ARR("",));
ArrayAuto(char*,EDIOQueryPWMfdRetNames,ARR("","freq","DC",));
ArrayAuto(char*,EDIOQuadratureCountRetNames,ARR("",));
ArrayAuto(char*,EDIOEdgeCountRetNames,ARR("",));
ArrayAuto(char*,EDIOGlitchedRetNames,ARR("",));
ArrayAuto(char*,EDIOHBridgeRetNames,ARR("",));
ArrayAuto(char**,EDIORetNames,ARR(ArrayL(EDIOLockRetNames),ArrayL(EDIOUnlockRetNames),ArrayL(EDIOPreemptRetNames),ArrayL(EDIOQueryFunctionRetNames),ArrayL(EDIOPWMRetNames),ArrayL(EDIOQueryPWMRetNames),ArrayL(EDIOPWMfdRetNames),ArrayL(EDIOQueryPWMfdRetNames),ArrayL(EDIOQuadratureCountRetNames),ArrayL(EDIOEdgeCountRetNames),ArrayL(EDIOGlitchedRetNames),ArrayL(EDIOHBridgeRetNames),));

ArrayAuto(char*,ModeJSONRetNames,ARR("",));
ArrayAuto(char*,ModeAssignRetNames,ARR("",));
ArrayAuto(char*,ModeNoAssignRetNames,ARR("",));
ArrayAuto(char*,ModeHexRetNames,ARR("",));
ArrayAuto(char*,ModeDecRetNames,ARR("",));
ArrayAuto(char*,ModeOctRetNames,ARR("",));
ArrayAuto(char*,ModeAStrRetNames,ARR("",));
ArrayAuto(char*,ModeAHexRetNames,ARR("",));
ArrayAuto(char*,ModeADecRetNames,ARR("",));
ArrayAuto(char*,ModeAOctRetNames,ARR("",));
ArrayAuto(char*,ModeABinOctRetNames,ARR("",));
ArrayAuto(char*,ModeABinHexRetNames,ARR("",));
ArrayAuto(char*,ModeABinUniRetNames,ARR("",));
ArrayAuto(char**,ModeRetNames,ARR(ArrayL(ModeJSONRetNames),ArrayL(ModeAssignRetNames),ArrayL(ModeNoAssignRetNames),ArrayL(ModeHexRetNames),ArrayL(ModeDecRetNames),ArrayL(ModeOctRetNames),ArrayL(ModeAStrRetNames),ArrayL(ModeAHexRetNames),ArrayL(ModeADecRetNames),ArrayL(ModeAOctRetNames),ArrayL(ModeABinOctRetNames),ArrayL(ModeABinHexRetNames),ArrayL(ModeABinUniRetNames),));

ArrayAuto(char***,RetNames,ARR(ArrayL(SystemRetNames),ArrayL(BusRetNames),ArrayL(TimeRetNames),ArrayL(PinRetNames),ArrayL(DIORawRetNames),ArrayL(DIORetNames),ArrayL(TWIRetNames),ArrayL(CANRetNames),ArrayL(SPIRetNames),ArrayL(AIORetNames),ArrayL(EDIORetNames),ArrayL(ModeRetNames),));

