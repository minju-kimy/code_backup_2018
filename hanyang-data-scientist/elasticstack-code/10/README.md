# 센서 데이터 분석 애플리케이션 구축

10장에서 필요한 데이터를 준비하기 위해 다음 단계를 실행하자.

1. 키바나 Dev Tools 화면에서 다음 명령을 실행해 인덱스 템플릿을 생성한다.

```shell
POST _template/sensor_data_template
{
  "index_patterns": ["sensor_data*"],
  "settings": {
      "number_of_replicas": "1",
      "number_of_shards": "5"
  },
  "mappings": {
    "doc": {
      "properties": {
        "sensorId": {
          "type": "integer"
        },
        "sensorType": {
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
        "buildingName": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "room": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "floor": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "locationOnFloor": {
          "type": "keyword",
          "fields": {
            "analyzed": {
              "type": "text"
            }
          }
        },
        "location": {
          "type": "geo_point"
        },
        "time": {
          "type": "date"
        },
        "reading": {
          "type": "double"
        }
      }
    }
  }
}
```

2. 로그스태시 최신 버전을 https://www.elastic.co/downloads/logstash 에서 다운로드하고 시스템에 설치한다.

3. 압축을 푼 로그스태시 디렉터리에 files 디렉터리를 복사하자. 예를 들면 로그스태시 설치 경로가 /usr/share/logstash와 같다면, 다음 명령을 실행하면 된다.

```shell
/usr/share/logstash/files/logstash_sensor_data_http.conf
```

4. 시스템에 MySQL 5.x 또는 PostgreSQL과 같은 관계형 데이터베이스를 설치해야 한다. 사용 중인 데이터베이스에 알맞은 JDBC 드라이버를 다운로드하자. MySQL JDBC 드라이버는 https://dev.mysql.com/downloads/connector/j 에서 다운로드할 수 있다.


5. Update the logstash_sensor_data_http.conf file and ensure that **jdbc_driver_library** has correct path to the MySQL JDBC driver jar. Verify that the variable **jdbc_connection_string** has the path to your MySQL database. Create a database called **sensor_metadata** in your MySQL database. Update the **jdbc_password** to the password of your MySQL database's password.

logstash_sensor_data_http.conf 파일에서 **jdbc_driver_library** 값을 업데이트하자. MySQL JDBC 드라이버의 jar 파일 경로를 정확히 입력해야 한다. MySQL에서 **sensor_metadata** 데이터베이스를 생성하고, **jdbc_connection_string** 값에 알맞은 MySQL 데이터베이스 경로를 지정하자. **jdbc_password** 값에는 MySQL 데이터베이스의 암호를 입력하면 된다.

6. MySQL Workbench 혹은 명랭행으로 MySQL Client를 실행해서 MySQL 데이터베이스에 로그인하자. 데이터베이스에서 files/create_sensor_metadata.sql 스크립트를 실행해 메타데이터를 로드하면 된다.

7. 다음 명령을 사용해 로그스태시를 시작한다.

```shell
cd /usr/share/logstash
bin/logstash -f files/logstash_sensor_data_http.conf
```

8. data/load_sensor_data.sh 스크립트를 실행해서 데이터를 로드한다.

```shell
./load_sensor_data.sh
```
