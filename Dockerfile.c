# 基于官方 PHP 8.1 镜像
FROM php:8.1-fpm-alpine


# 更新软件包源
RUN echo "https://mirrors.tuna.tsinghua.edu.cn/alpine/v3.18/main/" > /etc/apk/repositories; \
    echo "https://mirrors.tuna.tsinghua.edu.cn/alpine/v3.18/community/" >> /etc/apk/repositories;

COPY php.ini /usr/local/etc/php/php.ini  

# 安装基本的依赖和工具
RUN apk update && \
    apk add  --no-cache \
    nginx\
    curl \
    git \
    unzip \
    libzip-dev \
    libzip \
    oniguruma-dev \
    libpng \
    libpng-dev \
    libjpeg-turbo-dev \
    freetype-dev \
    autoconf g++ make \
    imagemagick-dev oniguruma-dev gettext-dev icu-dev \
    supervisor &&  \
    docker-php-ext-install pdo_mysql zip mbstring  opcache bcmath pcntl exif gd gettext intl  fileinfo zip \
    && pecl install redis imagick && docker-php-ext-enable redis pdo_mysql zip mbstring opcache bcmath pcntl exif gd gettext intl imagick && \
    curl -sS https://getcomposer.org/installer | php -- --install-dir=/usr/local/bin --filename=composer \
    && composer config -g repo.packagist composer https://mirrors.aliyun.com/composer/

#RUN chmod 755 -R /usr/local/lib/php/extensions/no-debug-non-zts-20210902/

EXPOSE 80 443 9000

# 复制 Nginx 配置文件到容器中
COPY nginx.conf /etc/nginx/nginx.conf

CMD php-fpm -D && nginx -g "daemon off;"
