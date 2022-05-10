该模块没有达到期望的目标，在filp_open一个文件后，file->f_op->write是null，所以不能直接使用。
