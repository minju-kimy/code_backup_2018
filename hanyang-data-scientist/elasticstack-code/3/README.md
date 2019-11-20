# 일래스틱서치에 데이터 가져오기

1. https://www.elastic.co/downloads/logstash 페이지에서 사용하는 운영체제에 알맞은 최신 버전의 로그스태시를 다운로드한다. 책에서 사용하는 버전은 6.0.0이다.
2. 다운받은 로그스태시를 설치한다.
3. 설치한 로그스태시 경로에 files 디렉터리를 복사한다. 로그스태시를 /usr/share/logstash 경로에 설치했다면 복사한 파일은 다음과 같을 것이다.

```shell
/usr/share/logstash/files/products.csv
/usr/share/logstash/files/logstash_products.conf
```

4. logstash_products.conf 파일에서 products.csv 파일 경로를 수정한다.


```
input {
  file {
    path => "/usr/share/logstash/files/products.csv"
    ...
```

5. 키바나 Dev Tools 페이지에서 다음 명령을 실행해 인덱스를 생성한다.

```shell
PUT /amazon_products
{
  "settings": {
    "number_of_shards": 1,
    "number_of_replicas": 0,
    "analysis": {
      "analyzer": {}
    }
  },
  "mappings": {
    "products": {
      "properties": {
        "id": {
          "type": "keyword"
        },
        "title": {
          "type": "text"
        },
        "description": {
          "type": "text"
        },
        "manufacturer": {
          "type": "text",
          "fields": {
            "raw": {
              "type": "keyword"
            }
          }
        },
        "price": {
          "type": "scaled_float",
          "scaling_factor": 100
        }
      }
    }
  }
}
```

6. 인덱스를 만들었다면 로그스태시를 실행한다.

```shell
cd /usr/share/logstash
bin/logstash -f files/logstash_products.conf
```
