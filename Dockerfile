# 基于官方 PHP 8.1 镜像
FROM registry.cn-guangzhou.aliyuncs.com/yansoa/php-alpine:8.1.21
#FROM yileo-alpine:1.0
COPY . /var/www/html/
COPY ./.env /var/www/html/

WORKDIR /var/www/html
RUN yes | composer update --no-dev && \
    chmod -R 755 . && \
    chown -R www-data:www-data . && \
    php artisan optimize

