#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "SingleMap.h"


top_map* alloc_map(){
    top_map* m = (top_map*)malloc(sizeof(top_map));
    m->ite = 0;
    m->total_length = 0;
    m->size = 32;
    m->keys = malloc(sizeof(char*) * m->size);
    m->values = malloc(sizeof(char*) * m->size);
    m->need_sign = malloc(sizeof(char) * m->size);
    m->value_lens = malloc(sizeof(size_t) * m->size);
    return m;
}

int insert_map_nosign(top_map* m,const char* key, const char* value, size_t val_len,char sign) {
    
    char * tk,*tv;
    size_t len;
    if(!key || !value || !m)
        return -1;
    
    len = strlen(key);
    tk = (char*) malloc(sizeof(char)*len+1);
    memmove(tk, key, len);
    tk[len] = '\0';
    m->total_length += len;
    
    tv = (char*) malloc(sizeof(char)*val_len+1);
    tv[val_len] = '\0';
    memmove(tv, value, val_len);
    m->total_length += val_len;
    
    if(m->ite == m->size){
        int i;
        char** tmp = NULL;
        char* signTmp = NULL;
        size_t* lenTmp = NULL;
        
        m->size = m->size * 2;
        tmp = malloc(sizeof(char*)* m->size);
        assert(tmp != NULL);
        for(i = 0; i < m->ite ;i++){
            tmp[i] = m->keys[i];
        }
        free(m->keys);
        m->keys = tmp;
        
        tmp = malloc(sizeof(char*)* m->size);
        assert(tmp != NULL);
        for(i = 0; i < m->ite ;i++){
            tmp[i] = m->values[i];
        }
        free(m->keys);
        m->values = tmp;
        
        signTmp = malloc(sizeof(char)* m->size);
        memmove(signTmp,m->need_sign,m->ite);
        free(m->need_sign);
        m->need_sign = signTmp;
        m->need_sign[m->ite] = 0;
        
        lenTmp = malloc(sizeof(int) * m->size);
        memmove(lenTmp,m->value_lens,m->ite * sizeof(int));
        free(m->value_lens);
        m->value_lens = lenTmp;
    }
    
    m->keys[m->ite] = tk;
    m->values[m->ite] = tv;
    m->value_lens[m->ite] = val_len;
    m->need_sign[m->ite] = sign;
    m->ite = m->ite + 1;
    
    return m->ite;
}

int insert_map(top_map* m,const char* key, const char* value){
    if(key == NULL || value == NULL){
        return 0;
    }
    return insert_map_nosign(m,key,value,strlen(value),1);
}

void destrop_map(top_map* m){
    if(m){
        int i ;
        for(i = 0; i < m->ite; i++){
            free(m->keys[i]);
            free(m->values[i]);
        }
        free(m->keys);
        free(m->values);
        free(m->need_sign);
        free(m->value_lens);
        free(m);
    }
}

void quiksort_(top_map* m,int low,int high)
{
    int i = low;
    int j = high;
    char** keys = m->keys;
    char** values = m->values;
    size_t* lens = m->value_lens;
    char* signs = m->need_sign;
    char* tempKey = keys[i];
    char* tempValue = values[i];
    char tmpSign = signs[i];
    size_t tempLen = lens[i];
    if( low < high)
    {
        while(i < j)
        {
            while((strcmp(keys[j], tempKey) >= 0) && (i < j))
            {
                j--;
            }
            keys[i] = keys[j];
            values[i] = values[j];
            lens[i] = lens[j];
            signs[i] = signs[j];
            
            while((strcmp(keys[i], tempKey) < 0) && (i < j))
            {
                i++;
            }
            keys[j]= keys[i];
            values[j] = values[i];
            lens[j] = lens[i];
            signs[j] = signs[i];
        }
        keys[i] = tempKey;
        values[i] = tempValue;
        lens[i] = tempLen;
        signs[i] = tmpSign;
        
        quiksort_(m,low,i-1);
        quiksort_(m,j+1,high);
    }
    else
    {
        return;
    }
}

void quiksort_by_key(top_map* m){
    quiksort_(m,0,m->ite - 1);
}

