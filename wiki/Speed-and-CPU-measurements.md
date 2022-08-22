I started to make some simple download measurements just for the record.

Local network, 100Mbps, Single file, 465453147 bytes of gzipped data

Tool|real|user|sys|Remarks
----|----|----|---|-------
wget2|0m39.604s|0m0.628s|0m2.696s|$ wget2 http://oms-4/file.gz<br><br>Simple download using 1 thread. Before Giuseppe's patch.
wget2|0m39.864s0m|0m0.628s|0m5.784s|$ wget2 http://oms-4/file.gz<br><br>Simple download using 1 thread. After Giuseppe's patch.
rsync|0m39.751s|0m6.040s|0m3.420s|$ rsync oms-4:/var/www/html/file.gz .<br><br>Pretty much CPU consumption ?
curl|0m39.630s|0m1.804s|0m3.908s|$ curl -s http://oms-4/file.gz -o file.gz
wget|0m39.606s|0m1.016s|0m6.388s|$ wget -q http://oms-4/file.gz

