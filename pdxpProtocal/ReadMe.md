编译命令: 
    在/root/PDXP/pdxpProtocal/MyProtocol下:
    输入命令行：g++ MyProtocol.cpp ./jsoncpp/jsoncpp.cpp -I ./ -o testpdxp
    会编译生成testpdxp 文件，在/root/PDXP/pdxpProtocal/MyProtocol路径下运行该文件：./testpdxp 
运行成功后，控制台会打印输出：
<!-- 
    msg1 parser successful!
    msg2 parser successful!
    Head[VER=1,MID=12345,SID=987654321,DID=123456789,BID=987654321,Number=1,FLAG=0,BACKUP=0,DATE=1229,TIME=123456,LEN=71],Body:{"key":"id","op":"set","value":"9856"}

    Head[VER=1,MID=54321,SID=123456789,DID=987654321,BID=123456789,Number=2,FLAG=1,BACKUP=0,DATE=1229,TIME=654321,LEN=56],Body:{"key":"id","op":"get"}
-->

项目参考源码1：https://blog.csdn.net/acb0y/article/details/61421006
项目参考源码2:https://www.cnblogs.com/ssyfj/p/14016931.html#%E4%B8%89%E5%85%A8%E9%83%A8%E4%BB%A3%E7%A0%81%E8%A7%81%EF%BC%9Agithub500%E8%A1%8C%E4%B8%8D%E5%88%B0