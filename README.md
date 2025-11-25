# Medical-Image-CUDA-Learning

[![Language](https://img.shields.io/badge/language-C%2B%2B/CUDA-blue.svg)](https://en.cppreference.com/)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](./LICENSE)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-orange.svg)](https://github.com/your-username/Medical-Image-CUDA-Learning)

一个 **14个月系统化学习仓库**，记录从 C++ 基础 → 医学图像处理 → CUDA 并行计算 → 实战落地的完整学习路径，最终目标是打造高性能、工程化的医学图像 GPU 加速工具库。

## 🌟 仓库定位

本仓库不仅是「学习笔记与代码存档」，更是「可落地的技术成长路线图」：
- 面向 **有医学/工程背景、想入门 C++ + CUDA 并行计算** 的学习者；
- 聚焦 **医学图像处理场景**（2D/3D 图像滤波、分割、点云处理、CUDA 加速优化）；
- 兼顾「基础夯实」与「工程化落地」，从语法练习到开源项目发布，全程可复现。

## 📚 学习路线（14个月规划）

### 阶段一：C++ 基础与工程化（1-16周）
- 核心目标：掌握 C++ 从基础语法到现代特性，具备无依赖开发小型工具的能力；
- 关键内容：语法基础 → 面向对象 → 内存管理 → STL → 模板 → 多线程 → 静态库封装；
- 阶段成果：无 OpenCV 依赖的 **灰度图处理工具**（支持 BMP/PGM 加载、滤波、二值化）。

### 阶段二：医学图像处理基础（17-28周）
- 核心目标：理解医学图像特性，掌握经典处理算法，熟悉专业库使用；
- 关键内容：DICOM 解析（DCMTK）→ 图像增强 → 形态学操作 → 分割算法 → 3D 体数据处理（VTK/PCL）；
- 阶段成果：**3D 医学图像分割与点云提取系统**（支持 DICOM 序列处理、3D 滤波、Marching Cubes 可视化）。

### 阶段三：CUDA 并行计算入门（29-44周）
- 核心目标：掌握 CUDA 核心机制，实现 2D/3D 医学图像算法的 GPU 加速；
- 关键内容：CUDA 基础 → 内存模型 → 线程同步 → 2D/3D 图像加速 → 性能调优（Nsight/nvprof）；
- 阶段成果：**CUDA 加速医学图像处理系统**（支持 CPU/CUDA 算法对比，加速比≥10x）。

### 阶段四：实战提升与专业化应用（45-54周）
- 核心目标：攻克复杂场景，工程化封装，发布开源项目；
- 关键内容：3D 霍夫变换 → 图像拼接 → MRI 偏置场仿真 → 动态库封装 → TensorRT 融合；
- 阶段成果：开源项目 **Medical-Image-CUDA-Accelerator**（覆盖率≥70%，支持批量处理与跨平台）。

## 📂 仓库结构

```
Medical-Image-CUDA-Learning/
├── 00-Learning-Plan/       # 学习计划与进度管理（14周计划、每周任务、进度跟踪）
├── 01-CPP-Foundation/      # C++基础（语法→多线程→阶段项目）
├── 02-Medical-Image-Basic/ # 医学图像处理基础（DICOM→3D处理→阶段项目）
├── 03-CUDA-Foundation/     # CUDA基础（核函数→3D加速→阶段项目）
├── 04-Medical-Image-CUDA-Practice/ # 实战应用（复杂算法→开源项目）
├── 05-Common-Libs/         # 依赖库说明（DCMTK/VTK/PCL版本要求）
├── 06-Docs/                # 知识沉淀（学习笔记、FAQ、技术博客）
├── 07-Tools/               # 工具配置（CMake、调试脚本、格式化配置）
├── .gitignore              # Git忽略文件
├── LICENSE                 # 开源许可证
└── README.md               # 仓库总说明
```

## 🚀 快速开始

### 1. 软硬件环境要求
| 环境         | 要求                                                                 |
|--------------|----------------------------------------------------------------------|
| 操作系统     | Windows 10+/Linux (Ubuntu 20.04+)                                    |
| 编译器       | GCC 9+/Clang 11+/MSVC 2019+                                          |
| GPU          | NVIDIA GPU（算力≥6.0，支持 CUDA 11.0+，推荐 RTX 2060+/Tesla T4）     |
| 依赖库       | CUDA Toolkit 11.0+、DCMTK 3.6.7+、VTK 9.0+、PCL 1.12+、CMake 3.18+  |

### 2. 编译与运行
以阶段一项目 `GrayImageProcessor` 为例：
```bash
# 克隆仓库
git clone https://github.com/your-username/Medical-Image-CUDA-Learning.git
cd Medical-Image-CUDA-Learning

# 进入项目目录
cd 01-CPP-Foundation/06-Final-Project/GrayImageProcessor

# 编译（CMake）
mkdir build && cd build
cmake ..
make -j4  # Linux
# 或 cmake --build . --config Release （Windows）

# 运行示例（灰度图二值化）
./GrayImageProcessor --input ../test_data/lena.pgm --output lena_binary.pgm --threshold 128
```

### 3. 学习建议
1. 按「阶段→周次→项目」顺序学习，每个 `src` 文件夹的日常练习优先完成，再挑战周末项目；
2. 每个项目文件夹下的 `README.md` 包含详细思路与测试方法，建议先阅读再编码；
3. 定期更新 `00-Learning-Plan/Progress-Tracking.md`，记录问题与短板（如 CUDA 内存优化、DICOM 解析细节）；
4. 注重「对比学习」：CPU 实现与 CUDA 实现对比、不同优化方案（如共享内存 vs 全局内存）效果对比。

## 📖 核心资源

| 学习方向       | 推荐资源                                                                 |
|----------------|--------------------------------------------------------------------------|
| C++ 基础       | 《C++ Primer》、[CppReference](https://en.cppreference.com/)、侯捷《STL源码剖析》 |
| 医学图像处理   | 《医学图像处理与分析》（冈萨雷斯）、DCMTK/VTK/PCL 官方文档                |
| CUDA 并行计算  | 《CUDA C Programming Guide》、《CUDA 高性能并行计算》、NVIDIA 开发者博客  |
| 性能优化       | Nsight Profiler 官方教程、《CUDA 并行程序设计：GPU 编程指南》             |

## 🤝 贡献与交流
- 欢迎 Fork 仓库，提交 PR（补充笔记、修复代码 Bug、优化编译配置）；
- 遇到问题可在 Issues 区提问，标注「阶段+周次+问题类型」（如「阶段三第32周 CUDA 归约求和错误」）；
- 如需技术交流，可通过邮箱联系：your-email@example.com。

## 📄 许可证
本仓库采用 [MIT 许可证](./LICENSE)，允许非商业/商业使用、修改、分发，需保留原作者版权声明。

---

**学习是一个持续迭代的过程**，本仓库会随学习进度不断更新代码、笔记与项目。如果对你有帮助，欢迎 Star 🌟 支持，一起成长为「C++ + CUDA + 医学图像处理」领域的工程师！
