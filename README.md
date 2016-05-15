# crawl
apt-get install curl libcurl3 libcurl3-dev php5-curl

echo "# crawl" >> README.md
git init
git add README.md
git commit -m "first commit"
git remote add origin https://github.com/maxingjiang/crawl.git
git push -u origin master

tcpdump -i eth0 host 192.168.88.128 -w tcpdump.log
