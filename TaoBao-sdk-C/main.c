#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include "topsdk.h"


char* url = "http://api.daily.taobao.net/router/rest?";
char* appkey = "4272";
char* appsecret = "0ebbcccfee18d7ad1aebc5b135ffa906";

char* httpsUrl = "https://eco.taobao.com/router/rest?" ;
char* appkey_ol = "12497914";
char* appsecret_ol = "4b0f28396e072d67fae169684613bcd1";

void testUserGet(){
    int i;
    for(i = 0 ; i < 5; i++){
        pTopRequest pRequest = alloc_top_request();
        pTopResponse pResponse = NULL;
        pTaobaoClient pClient = alloc_taobao_client(url, appkey, appsecret);
        set_api_name(pRequest,"taobao.user.get");
        add_param(pRequest, "fields", "nick,type,sex,location");
        add_param(pRequest, "nick", "sandbox_c_1");
    
        pResponse = top_execute(pClient,pRequest,NULL);
        printf("ret code:%d\n",pResponse->code);
        if(pResponse->code == 0){
            pTopResponseIterator ite = init_response_iterator(pResponse);
            pResultItem pResultItem = alloc_result_item();
            while(parseNext(ite, pResultItem) == 0){
                printf("%s:%s\n",pResultItem->key,pResultItem->value);
            }
            destroy_response_iterator(ite);
            destroy_result_item(pResultItem);
        }
        destroy_top_request(pRequest);
        destroy_top_response(pResponse);
        destroy_taobao_client(pClient);
    }
}

void testByteArray(){
    int i;
    for(i = 0 ; i < 100; i++){
        pTopRequest pRequest = alloc_top_request();
        pTopResponse pResponse = NULL;
        pTaobaoClient pClient = alloc_taobao_client(url, appkey, appsecret);
        set_api_name(pRequest,"taobao.topapi.test");
        add_param(pRequest, "appkey", "4272");
        add_memoryfile_param(pRequest, "content", "111111111111111111",strlen("111111111111111111"));
        add_param(pRequest, "expire_time", "100000");
        add_param(pRequest, "force_create", "true");
        add_param(pRequest, "file", "test.php");
        add_param(pRequest, "ts", "1513167176000");

        pResponse = top_execute(pClient,pRequest,"6100723e4de01a52a0fc3b734f46e551c38ef4cbee15da165753805");
        printf("ret code:%d\n",pResponse->code);
        if(pResponse->code == 0){
            printf("%s\n",pResponse->bytes);
        } else {
            printf("%s,%s\n",pResponse->msg,pResponse->subMsg);
        }
        
        destroy_top_request(pRequest);
        destroy_top_response(pResponse);
        destroy_taobao_client(pClient);

        sleep(1);
    }
}

void testHttps(){
    
    pTopRequest pRequest = alloc_top_request();
    pTopResponse pResponse = NULL;
    pTaobaoClient pClient = alloc_taobao_client(httpsUrl, appkey_ol, appsecret_ol);
    
    set_retry_times(3);
    set_retry_sleep_times(100);
    
    set_api_name(pRequest,"taobao.time.get");
    pResponse = top_execute(pClient,pRequest,NULL);
    
    printf("ret code:%d\n",pResponse->code);
    if(pResponse->code == 0){
        pTopResponseIterator ite = init_response_iterator(pResponse);
        pResultItem pResultItem = alloc_result_item();
        while(parseNext(ite, pResultItem) == 0){
            printf("%s:%s\n",pResultItem->key,pResultItem->value);
        }
        destroy_response_iterator(ite);
        destroy_result_item(pResultItem);
    }else{
         printf("Error Msg:%s\n",pResponse->msg);
         printf("Error Sub Msg:%s\n",pResponse->subMsg);
    }

    destroy_top_request(pRequest);
    destroy_top_response(pResponse);
    destroy_taobao_client(pClient);
}

int main(){
/*
    testUserGet();
    testByteArray();
*/
    testByteArray();
    return 0;
}

