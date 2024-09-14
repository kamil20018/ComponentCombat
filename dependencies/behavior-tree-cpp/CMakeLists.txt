message(STATUS "Fetching BehaviorTree.cpp...")

FetchContent_Declare(
    behavior-tree
    GIT_REPOSITORY "https://github.com/BehaviorTree/BehaviorTree.CPP"
    GIT_TAG 2a8a226fbbd99f524f0796e0d8a3145773c61c06 # 4.6.2
)

FetchContent_MakeAvailable(behavior-tree)