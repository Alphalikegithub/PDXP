import shutil
import os

outpath = "../export_lib"   # -- 设置依赖库lib输出路径
os.makedirs(outpath) if not os.path.exists(outpath) else None

command = "ldd ./server"   # -- xxx更换为要打包的可执行文件名
out_string = os.popen(command)
data = out_string.readlines()
data = [[data_.split()[0], data_.split()[2]] for data_ in data if len(data_.split()) == 4]
print(data)

for data_ in data:
        shutil.copy(data_[1], os.path.join(outpath, data_[0]))
