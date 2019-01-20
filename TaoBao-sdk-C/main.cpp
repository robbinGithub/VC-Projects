#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
#include "topsdk.h"


const char* url = "http://api.daily.taobao.net/router/rest?" ;
const char* appkey = "4272";
const char* appsecret = "0ebbcccfee18d7ad1aebc5b135ffa906";

const char* httpsUrl = "https://eco.taobao.com/router/rest?" ;
const char* appkey_ol = "12497914";
const char* appsecret_ol = "4b0f28396e072d67fae169684613bcd1";

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
    for(i = 0 ; i < 5; i++){
        pTopRequest pRequest = alloc_top_request();
        pTopResponse pResponse = NULL;
        pTaobaoClient pClient = alloc_taobao_client(url, appkey, appsecret);
        set_api_name(pRequest,"taobao.chengxian.bytetest");
        
        pResponse = top_execute(pClient,pRequest,NULL);
        printf("ret code:%d\n",pResponse->code);
        if(pResponse->code == 0){
            printf("%s\n",pResponse->bytes);
        }
        destroy_top_request(pRequest);
        destroy_top_response(pResponse);
        destroy_taobao_client(pClient);
    }
}

void testHttps(){
    
    pTopRequest pRequest = alloc_top_request();
    pTopResponse pResponse = NULL;
    pTaobaoClient pClient = alloc_taobao_client(httpsUrl, appkey_ol, appsecret_ol);
    
	//char *capth = "./cacert.pem";
    //set_capath(capth);
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

    testUserGet();
   // testByteArray();

   // testHttps();
    return 0;
}

