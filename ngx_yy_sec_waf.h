#ifndef __YY_SEC_WAF_H__
#define __YY_SEC_WAF_H__

/*
** @file: ngx_yy_sec_waf.h
** @description: This is the header file for yy sec waf.
** @author: dw_liqi1<liqi1@yy.com>
** @date: 2013.07.10
** Copyright (C) YY, Inc.
*/

#include <nginx.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include <ngx_event.h>
#include <ngx_string.h>

#define STR "str:"
#define REGEX "regex:"
#define EQ "eq:"
#define MOD "mod:"
#define GIDS "gids:"
#define ID "id:"
#define MSG "msg:"
#define POS "pos:"
#define LEVEL "lev:"

/* POS */
#define HEADER "HEADER"
#define BODY "BODY"
#define URI "URI"
#define ARGS "ARGS"
#define COOKIE "COOKIE"

/* LEV */
#define LOG "LOG"
#define BLOCK "BLOCK"
#define ALLOW "ALLOW"

#define RULE_MATCH              1
#define RULE_NO_MATCH           2

int ngx_yy_sec_waf_unescape(ngx_str_t *str);

ngx_int_t ngx_http_yy_sec_waf_execute_null(ngx_http_request_t *r,
    ngx_str_t *str, void *rule);


typedef void* (*fn_op_parse_t)(ngx_conf_t *cf,
    ngx_str_t *tmp, void *rule);
typedef ngx_int_t (*fn_op_execute_t)(ngx_http_request_t *r,
    ngx_str_t *str, void *rule);

typedef struct {
    const char *name;
    fn_op_parse_t parse;
    fn_op_execute_t execute;
} re_op_metadata;

extern ngx_module_t  ngx_http_yy_sec_waf_module;
extern re_op_metadata op_metadata[];

typedef struct ngx_http_yy_sec_waf_rule {
    ngx_str_t *str; /* STR */
    ngx_http_regex_t *regex; /* REG */
    ngx_str_t *eq; /* EQ */
    ngx_flag_t mod:1; /* MOD */
    ngx_str_t *gids; /* GIDS */
    ngx_str_t *msg; /* MSG */
    ngx_int_t  rule_id;
    ngx_int_t  var_index;

    re_op_metadata *op_metadata;

    /* POS */
    ngx_flag_t body:1;
    ngx_flag_t header:1;
    ngx_flag_t uri:1;
    ngx_flag_t args:1;
    ngx_flag_t cookie:1;
    ngx_flag_t variable:1;
    /* LEVEL*/
    ngx_flag_t    log:1;
    ngx_flag_t    block:1;
    ngx_flag_t    allow:1;
} ngx_http_yy_sec_waf_rule_t;

typedef struct {
    ngx_array_t *header_rules;/* ngx_http_yy_sec_waf_rule_t */
    ngx_array_t *args_rules;
    ngx_array_t *uri_rules;
    ngx_array_t *variable_rules;

    ngx_str_t *denied_url;
    ngx_uint_t http_method;
    ngx_uint_t max_post_args_len;
    ngx_flag_t enabled;

    /* count */
    ngx_uint_t    request_processed;
    ngx_uint_t    request_matched;
    ngx_uint_t    request_blocked;
} ngx_http_yy_sec_waf_loc_conf_t;

typedef struct {
    /* blocking flags*/
    ngx_flag_t    log:1;
    ngx_flag_t    block:1;
    ngx_flag_t    allow:1;
    /* state */
    ngx_flag_t    process_done:1;
    ngx_flag_t    read_body_done:1;
    ngx_flag_t    waiting_more_body:1;

    ngx_flag_t    matched:1;
    ngx_int_t     rule_id;
    ngx_str_t    *gids;
    ngx_str_t    *msg;
    ngx_str_t    *matched_string;
} ngx_http_request_ctx_t;


#endif

