//
// Created by Good_Pudge.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "headers.hpp"
#include "cache_control.hpp"
#include "cookie.hpp"
#include "form_body.hpp"
#include "http_url.hpp"
#include "inet_address.hpp"
#include "media_type.hpp"
/**
 * std::vector<Part> mParts is null in `MultipartBody` class.
 * But if I run simple program - all right.
 */
// #include "multipart_body.hpp"
#include "request.hpp"
#include "request_body.hpp"
#include "time_unit.hpp"