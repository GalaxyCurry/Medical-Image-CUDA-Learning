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
- 如需技术交流，可通过邮箱联系：lmy15933285944@163.com。

## 📄 许可证
本仓库采用 [MIT 许可证](./LICENSE)，允许非商业/商业使用、修改、分发，需保留原作者版权声明。

---

**学习是一个持续迭代的过程**，本仓库会随学习进度不断更新代码、笔记与项目。如果对你有帮助，欢迎 Star 🌟 支持，一起成长为「C++ + CUDA + 医学图像处理」领域的工程师！






## 📂 仓库结构详细内容

```
Medical-Image-CUDA-Learning/
├── 00-Learning-Plan/                # 学习计划与进度管理
│   ├── 14-Month-Plan.docs           # 完整14个月学习计划（复刻文档核心内容）
│   ├── Weekly-Tasks/                # 每周任务分解（可按周次建子文件夹，存放每日学习笔记）
│   ├── Progress-Tracking.docs       # 学习进度跟踪（已完成模块、待补短板）
│   └── Hardware-Software-Requirements.md  # 软硬件要求（GPU算力、依赖库版本）
├── 01-CPP-Foundation/               # 阶段一：C++基础（1-16周）
│   ├── 01-Syntax-Basics/            # 第1-2周：语法基础、指针与数组
│   │   ├── gray-image-threshold/    # 周末项目：灰度图阈值分割（传值/传引用对比）
│   │   ├── matrix-add/              # 周末项目：指针实现矩阵加法
│   │   └── src/                     # 日常练习代码（变量、循环、指针操作等）
│   ├── 02-OOP/                      # 第3-4周：面向对象（类与对象、继承多态）
│   │   ├── Image-Class-Basic/       # 周末项目：基础Image类（深拷贝）
│   │   ├── Image-Class-Inheritance/ # 周末项目：Image类继承与多态（GrayImage/ColorImage）
│   │   └── src/                     # 日常练习（构造函数、虚函数、抽象类等）
│   ├── 03-Memory-Management/        # 第5周：动态内存与智能指针
│   │   ├── Image-Class-SmartPointer/ # 周末项目：智能指针重构Image类
│   │   └── src/                     # 日常练习（new/delete、shared_ptr/unique_ptr等）
│   ├── 04-STL/                      # 第6-8周：STL容器与算法
│   │   ├── image-pixel-storage/     # 周末项目：vector存储图像像素
│   │   ├── image-metadata-map/      # 周末项目：map管理图像元数据
│   │   ├── pixel-filter-sort/       # 周末项目：STL算法实现像素筛选与排序
│   │   └── src/                     # 日常练习（vector/map/for_each/sort等）
│   ├── 05-Advanced-CPP/             # 第9-16周：模板、内存优化、现代C++、多线程等
│   │   ├── template-matrix/         # 周末项目：模板化矩阵类
│   │   ├── variadic-template-sum/   # 周末项目：可变参数模板求和
│   │   ├── image-filter-cache-opt/  # 周末项目：均值滤波缓存优化
│   │   ├── image-processor-static-lib/ # 周末项目：图像处理静态库封装
│   │   ├── Image-Class-ModernCPP/   # 周末项目：现代C++重构Image类（移动语义、emplace_back）
│   │   ├── dicom-file-filter/       # 周末项目：正则匹配DICOM文件
│   │   ├── multi-thread-image-filter/ # 周末项目：多线程图像滤波
│   │   └── src/                     # 日常练习（异常处理、模板、内存对齐、多线程等）
│   └── 06-Final-Project/            # 第16周：阶段综合项目
│       ├── GrayImageProcessor/       # 无OpenCV依赖的灰度图处理工具（BMP/PGM加载、滤波、二值化）
│       │   ├── src/                 # 源码（IO模块、滤波模块、命令行解析）
│       │   ├── build/               # 编译产物
│       │   └── README.md            # 项目说明与使用教程
├── 02-Medical-Image-Basic/          # 阶段二：医学图像处理基础（17-28周）
│   ├── 01-DICOM-Parsing/            # 第17周：DICOM格式解析
│   │   ├── dicom-parser-tool/       # 周末项目：DICOM文件解析工具（提取元数据+转灰度图）
│   │   └── src/                     # 日常练习（DCMTK库使用）
│   ├── 02-Image-Enhancement/        # 第18-21周：灰度变换、滤波（线性/非线性）
│   │   ├── medical-image-noise-analysis/ # 周末项目：CT图像噪声分析（HU值分布、PSNR）
│   │   ├── gray-enhancement-tool/   # 周末项目：灰度增强工具（线性拉伸、伽马校正、直方图均衡化）
│   │   ├── edge-detection-linear/   # 周末项目：Sobel/Prewitt边缘检测
│   │   ├── edge-preserving-filter/  # 周末项目：中值/双边/导向滤波（保边降噪）
│   │   └── src/                     # 日常练习（卷积运算、高斯核生成等）
│   ├── 03-Image-Segmentation/       # 第22-24周：形态学操作、阈值分割、边缘/区域分割
│   │   ├── morphological-processing/ # 周末项目：形态学处理工具（腐蚀/膨胀/梯度）
│   │   ├── threshold-segmentation/  # 周末项目：阈值分割工具（Otsu/自适应阈值）
│   │   ├── medical-segmentation-lib/ # 周末项目：分割库（Canny/区域生长/分水岭）
│   │   └── src/                     # 日常练习（形态学操作、Dice系数计算等）
│   ├── 04-3D-Medical-Image/         # 第25-27周：3D体数据、3D滤波、点云处理
│   │   ├── 3d-dicom-sequence-parser/ # 周末项目：3D DICOM序列处理工具（切片提取）
│   │   ├── 3d-filter-pointcloud/    # 周末项目：3D滤波与点云提取（Marching Cubes）
│   │   ├── medical-pointcloud-processing/ # 周末项目：点云下采样/去噪/法线计算
│   │   └── src/                     # 日常练习（3D数组、VTK可视化、PCL库使用等）
│   └── 05-Final-Project/            # 第28周：阶段综合项目
│       ├── 3D-Medical-Segmentation-PointCloud/ # 3D医学图像分割与点云提取系统
│           ├── src/                 # 源码（IO/滤波/分割/点云模块）
│           ├── build/               # 编译产物
│           └── README.md            # 项目说明与测试报告
├── 03-CUDA-Foundation/              # 阶段三：CUDA并行计算入门（29-44周）
│   ├── 01-CUDA-Basics/              # 第29-33周：CUDA基础、内存模型、线程同步
│   │   ├── cuda-hello-world/        # 第29周：环境测试（Hello World）
│   │   ├── cuda-vector-add/         # 第30周：CUDA向量加法（核函数+错误处理）
│   │   ├── cuda-vector-add-memory/  # 第31周：向量加法（全局内存/常量内存对比）
│   │   ├── cuda-reduction-sum/      # 第32周：共享内存优化并行归约求和
│   │   ├── cuda-histogram/          # 第33周：并行直方图计算（原子操作）
│   │   └── src/                     # 日常练习（线程索引计算、cudaMalloc、__syncthreads等）
│   ├── 02-2D-Medical-Image-CUDA/    # 第34-36周：2D医学图像CUDA加速
│   │   ├── cuda-2d-gaussian-filter/ # 周末项目：CUDA 2D高斯滤波（全局/共享内存）
│   │   ├── cuda-2d-medical-algorithms/ # 周末项目：CUDA 2D医学算法库（阈值分割、Canny等）
│   │   ├── cuda-2d-gaussian-stream/ # 周末项目：流优化2D高斯滤波（单流/多流）
│   │   └── src/                     # 日常练习（2D线程映射、边界Padding、异步执行等）
│   ├── 03-3D-PointCloud-CUDA/       # 第37-41周：3D体数据、点云CUDA加速
│   │   ├── cuda-3d-median-filter/   # 周末项目：CUDA 3D中值滤波
│   │   ├── cuda-3d-gaussian-optimized/ # 周末项目：可分离+共享内存优化3D高斯滤波
│   │   ├── cuda-pointcloud-downsample-denoise/ # 周末项目：并行点云下采样与去噪
│   │   ├── cuda-pointcloud-normal/  # 周末项目：并行点云表面法线计算
│   │   ├── cuda-mixed-precision-3d-conv/ # 周末项目：混合精度3D卷积
│   │   └── src/                     # 日常练习（3D线程映射、可分离卷积、混合精度等）
│   ├── 04-CUDA-Optimization-Debug/  # 第42-43周：性能调优与健壮性设计
│   │   ├── cuda-3d-gaussian-profiling/ # 周末项目：3D高斯滤波性能调优（Nsight/nvprof）
│   │   ├── cuda-medical-lib-robust/ # 周末项目：CUDA算法库健壮性重构（错误检查、内存泄漏修复）
│   │   └── src/                     # 日常练习（性能分析工具使用、错误处理宏等）
│   └── 05-Final-Project/            # 第44周：阶段综合项目
│       ├── CUDA-Medical-Image-Processor/ # CUDA加速2D/3D医学图像处理系统
│           ├── src/                 # 源码（IO模块、CPU/CUDA算法模块、可视化模块）
│           ├── build/               # 跨平台编译产物（Windows/Linux）
│           ├── docs/                # API文档、编译指南
│           └── performance-report/  # 性能报告（加速比、GPU利用率）
├── 04-Medical-Image-CUDA-Practice/  # 阶段四：实战提升与专业化应用（45-54周）
│   ├── 01-3D-Cylinder-Detection/    # 第45-46周：3D霍夫变换圆柱体检测
│   │   ├── cpu-hough-transform/     # 周末项目：CPU版3D霍夫变换
│   │   ├── cuda-hough-transform/    # 周末项目：CUDA版3D霍夫变换（并行投票+内存优化）
│   │   └── src/                     # 日常练习（参数空间分块、原子操作优化等）
│   ├── 02-Medical-Image-Stitching/  # 第47-48周：医学图像拼接
│   │   ├── cpu-sift-stitching/      # 周末项目：CPU版SIFT图像拼接
│   │   ├── cuda-sift-stitching/     # 周末项目：CUDA版SIFT拼接（并行特征提取/匹配）
│   │   └── src/                     # 日常练习（尺度空间构建、FLANN匹配并行化等）
│   ├── 03-MRI-Bias-Field/           # 第49周：MRI偏置场仿真
│   │   ├── cuda-bias-field-simulation/ # 周末项目：CUDA加速MRI偏置场仿真
│   │   └── src/                     # 日常练习（多项式/高斯偏置场模型、批量处理等）
│   ├── 04-Engineering-Encapsulation/ # 第50-51周：工程化封装与批量调度
│   │   ├── MedicalImageCudaLib/     # 周末项目：动态库封装（统一接口、模板化）
│   │   ├── batch-medical-processing/ # 周末项目：批量医学图像处理系统（线程池+内存池）
│   │   └── src/                     # 日常练习（CMake配置、跨平台编译、任务队列等）
│   ├── 05-Open-Source-Project/      # 第52周：开源项目发布
│   │   ├── Medical-Image-CUDA-Accelerator/ # 开源项目核心代码
│   │   ├── docs/                    # API文档（Doxygen生成）、贡献指南
│   │   ├── tests/                   # Google Test测试用例（覆盖率≥70%）
│   │   ├── benchmarks/              # 性能基准报告（对比CPU/OpenCV-CUDA/PCL-GPU）
│   │   ├── README.md                # 开源项目说明（功能、编译、使用示例）
│   │   └── LICENSE                  # 开源许可证
│   └── 06-Advanced-Exploration/     # 第53-54周：TensorRT融合与技术复盘
│       ├── cuda-tensorrt-unet/      # 周末项目：CUDA+TensorRT混合分割系统（U-Net）
│       ├── learning-summary-report/ # 学习总结报告（技术栈、项目成果、优化案例）
│       ├── interview-prep/          # 面试准备（C++/CUDA算法题）
│       └── future-learning-plan/    # 长期学习计划
├── 05-Common-Libs/                  # 公共依赖库与工具
│   ├── dcmtk/                       # DCMTK库（DICOM解析）
│   ├── vtk/                         # VTK库（3D可视化）
│   ├── pcl/                         # PCL库（点云处理）
│   ├── opencv/                      # OpenCV（对比验证结果）
│   └── cmake-modules/               # 通用CMake模块（跨平台编译配置）
├── 06-Docs/                         # 知识沉淀与文档
│   ├── cpp-notes/                   # C++学习笔记（语法、STL、现代C++等）
│   ├── medical-image-notes/         # 医学图像处理笔记（DICOM、滤波、分割等）
│   ├── cuda-notes/                  # CUDA学习笔记（内存模型、线程模型、优化技巧等）
│   ├── resources/                   # 学习资源（书籍、博客、官方文档链接）
│   ├── faq/                         # 常见问题（编译错误、GPU适配、性能瓶颈）
│   └── technical-blogs/             # 技术博客（核心优化思路、项目复盘）
├── 07-Tools/                        # 工具配置与辅助脚本
│   ├── cmake/                       # 全局CMake配置（CMakeLists.txt模板）
│   ├── scripts/                     # 辅助脚本（编译脚本、性能测试脚本、批量处理脚本）
│   ├── debug/                       # 调试配置（VS Code/GDB调试文件）
│   └── format/                      # 代码格式化（Clang-Format配置文件）
├── .gitignore                       # Git忽略文件（编译产物、IDE配置、日志等）
└── README.md                        # 仓库总说明（结构介绍、学习路线、快速开始）
```