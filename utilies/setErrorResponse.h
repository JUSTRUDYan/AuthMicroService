//
// Created by steam on 10.11.2024.
//

#include "wfrest/HttpServer.h"

using namespace wfrest;

void setErrorResponse(HttpResp *resp, int statusCode, const std::string& message) {
    resp->set_status(statusCode);
    Json errorJson;
    errorJson["error"] = message;
    resp->Json(errorJson);
}