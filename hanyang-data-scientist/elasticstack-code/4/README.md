# 일래스틱서치의 분석 기능을 배우기 위해 네트워크 트래픽 데이터 가져오기

1번과 2번 단계는 로그스태시가 시스템에 설치되지 않은 경우에만 실행한다.

1. https://www.elastic.co/downloads/logstash 페이지에서 사용하는 운영체제에 알맞은 최신 버전의 로그스태시를 다운로드한다. 책에서 사용하는 버전은 6.0.0이다.
2. 다운받은 로그스태시를 설치한다.
3. 설치한 로그스태시 경로에 files 디렉터리를 복사한다. 로그스태시를 /usr/share/logstash 경로에 설치했다면 복사한 파일은 다음과 같을 것이다.

```shell
/usr/share/logstash/files/network_traffic_data.zip
/usr/share/logstash/files/logstash_network_traffic_data.conf
```

4. network_traffic_data.zip 압축을 풀고 network_traffic_data.json 파일을 생성한다.

```shell
/usr/share/logstash/files/network_traffic_data.json
```

5. logstash_network_traffic_data.conf 파일에서 network_traffic_data.json 파일의 절대 경로가 올바른지 확인한다.
6. 키바나 Dev Tools 페이지에서 다음 명령을 실행해 인덱스를 생성한다.

```shell
PUT /bigginsight
{
  "settings": {
    "index": {
      "number_of_replicas": "1",
      "number_of_shards": "5"
    }
  },
  "mappings": {
    "usageReport": {
      "properties": {
        "accessPointId": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "application": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "band": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "bandwidth": {
          "type": "double"
        },
        "category": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "customer": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "department": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "downloadCurrent": {
          "type": "double"
        },
        "downloadTotal": {
          "type": "integer"
        },
        "inactiveMs": {
          "type": "integer"
        },
        "location": {
          "type": "geo_point"
        },
        "mac": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "networkId": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "signalStrength": {
          "type": "integer"
        },
        "time": {
          "type": "date",
          "format": "strict_date_optional_time||epoch_millis"
        },
        "uploadCurrent": {
          "type": "double"
        },
        "uploadTotal": {
          "type": "integer"
        },
        "usage": {
          "type": "double"
        },
        "username": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        }
      }
    }
  }
}
```

7. 인덱스를 만들었다면 로그스태시를 실행한다.

```shell
cd /usr/share/logstash
bin/logstash -f files/logstash_network_traffic_data.conf
```
