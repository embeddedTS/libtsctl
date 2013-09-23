void *ServerTCP(void *arg);
typedef struct {
  ThreadFunction f;
  void *(*constor)(int socket);
  ThreadDestructor destor;
} ServerData;
