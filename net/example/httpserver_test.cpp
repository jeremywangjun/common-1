#include <string>
#include <iostream>
#include "http/httpserver.h"
#include "httpcodec.h"
#include <string.h>
#include "favicon.h"

using namespace std;
bool benchmark = false;
int onRequest(const HttpRequest& req, HttpResponse* resp) {
    std::cout << "Headers " << req.methodString() << " " << req.path() << std::endl;
    if (!benchmark) {
        const std::map<string, string>& headers = req.headers();
        for (std::map<string, string>::const_iterator it = headers.begin();
            it != headers.end();
            ++it)
        {
            std::cout << it->first << ": " << it->second << std::endl;
        }
    }

    if (req.path() == "/") {
        resp->setStatusCode(HttpResponse::k200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType("text/html");
        resp->addHeader("Server", "HttpServer");

        resp->setBody("<html><head><title>This is title</title></head>"
            "<body><h1>Hello</h1>Now is " + std::to_string(time(NULL)) +
            "</body></html>");
    }
    else if (req.path() == "/favicon.ico") {
        resp->setStatusCode(HttpResponse::k200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType("image/png");
        resp->setBody(string(favicon, sizeof favicon));
    }
    else if (req.path() == "/hello") {
        resp->setStatusCode(HttpResponse::k200Ok);
        resp->setStatusMessage("OK");
        resp->setContentType("text/plain");
        resp->addHeader("Server", "HttpServer");
        resp->setBody("hello, world!\n");
    }
    else {
        resp->setStatusCode(HttpResponse::k404NotFound);
        resp->setStatusMessage("Not Found");
        resp->setCloseConnection(true);
        resp->setBody("404 Not Found\n");
    }
    return RET_OK;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        return -1;
    }
    TcpServer tcp;
    tcp.initData();
    tcp.initCallBack();
    tcp.getBufferEvent()->setCodec(new HttpCodec);
    int listenfd = tcp.bind(argv[1], atoi(argv[2]));
    tcp.setAcceptInfo(listenfd);
    HttpServer http(&tcp);
    http.setHttpCallback(onRequest);
    http.start();
    return 0;
}