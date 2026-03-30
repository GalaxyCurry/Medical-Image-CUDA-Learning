// 当前使用用户
whoami
//当前使用节点
hostname
//查看CPU信息
lscpu
//查看内存信息
free -h
//监视进程和Linux系统资源top
//查看磁盘使用情况df -h
//查看当前路径pwd
//查看当前路径下的文件和文件夹ls -l
//查看当前路径下的所有文件和文件夹ls -a
//查看当前路径下的所有文件和文件夹ls -la
//查看文件名带有name的文件ls -l *name*
//查看文件名以name开头的文件ls -l name*
//查看文件名以name结尾的文件ls -l *name

//查看文件内容cat filename
//查看文件内容并分页显示less filename
//查看文件内容并分页显示more filename
//查看文件内容的前10行head filename
//查看文件内容的后10行tail filename

//目录切换cd /path/to/directory
//返回上一级目录cd ..
//返回用户主目录cd ~    
//返回根目录cd /
//返回上次所在目录cd -

//创建文件touch filename

//创建目录mkdir directory_name
//删除目录rmdir directory_name
//删除文件rm filename
//复制文件cp source_file destination_file
//移动文件mv source_file destination_file

//查看当前系统时间date

//文件和目录查找find /path -name "filename"
//在当前目录下查找文件find . -name "filename"
//在当前目录下查找目录find . -type d -name "directory_name"

//文件的字符搜索grep "search_string" filename
//在当前目录下搜索文件内容grep -r "search_string" .


//查看当前系统正在运行的进程ps aux
//杀死进程kill PID
//强制杀死进程kill -9 PID

//查看当前系统的IP地址ip addr

//命令行式文件编辑器 vim filename
//退出vim编辑器：按下Esc键，输入:q!，然后按Enter键
//保存编辑内容并退出vim编辑器：按下Esc键，输入:wq， 然后按Enter键


