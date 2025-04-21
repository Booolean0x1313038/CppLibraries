// 链式数据结构, 基于双向链表

#ifndef __LINKEDLIST_HPP__
#define __LINKEDLIST_HPP__

#include "../Math.hpp"
#include "initializer_list"

namespace _Boolean::Collections::Linked
{
    /// @brief 链表节点
    /// @tparam T
    template <typename T>
    struct Node
    {
    public:
        T Value;
        Node<T> *Next = nullptr;
        Node<T> *Preview = nullptr;

        Node(T v, Node<T> *pre = nullptr, Node<T> *next = nullptr)
        {
            Value = v;
            Preview = pre;
            Next = next;
        }
    };

    /// @brief 链表基础实现
    /// @tparam T
    template <typename T>
    class Base
    {
    private: /// 这里记录了上次查找结点时的结果和位置, 进行查找时可从 头 尾 上次位置 三者中选取更近的位置作为起始点进行查找
        Node<T> *_NodeCache = nullptr;
        int _NodeCacheIndex = 0;
        /// @brief 清空缓存信息, 在每次 add / remove 时都要进行清空
        void ClearCache()
        {
            _NodeCache = nullptr;
            _NodeCacheIndex = 0;
        }

    private:
        /// @brief 限制 index 在 [0, Length) 区间内
        /// @param index 值
        void LimitIndex(int &index)
        {
            if (_Count == 0)
            {
                index = 0;
            }
            else
            {
                if (index < 0)
                {
                    index += _Count;
                }
                index = _Boolean::Math::Min<int>(index, _Count - 1);
                index = _Boolean::Math::Max<int>(index, 0);
            }
        }

    public:
        Base<T>(){};

        /// @brief 清空链表
        void Clear()
        {
            while (_Start != nullptr)
            {
                Node<T> *node = _Start->Next;
                delete _Start;
                _Start = node;
            }
            _End = nullptr;
            _Count = 0;
            ClearCache();
        }

        /// @brief 链表长度
        /// @return 链表长度
        size_t Length() { return _Count; }

    protected:
        /// @brief 根据位置获得存储值的地址
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @return 值的地址, 如果没找到则为 nullptr (链表为空时才会出现, 因为查找时 index 会被限制在有效范围之内)
        T *Base_At(int index)
        {
            Node<T> *node = GetNode(index);
            return node != nullptr ? &(node->Value) : nullptr;
        }

        /// @brief 在链表结尾添加数据
        /// @param value 值
        void Base_InsertAtLast(T value)
        {
            Node<T> *newNode = new Node<T>(value);
            if (_Start == nullptr) // 链表为空
            {
                _Start = newNode;
            }
            else
            {
                _End->Next = newNode;
                newNode->Preview = _End;
            }
            _End = newNode;
            ++_Count;
            ClearCache();
        }

        /// @brief 在链表开头添加数据
        /// @param value 值
        void Base_InsertAtFirst(T value)
        {
            Node<T> *newNode = new Node<T>(value);
            if (_End == nullptr) // 链表为空
            {
                _End = newNode;
            }
            else
            {
                _Start->Preview = newNode;
                newNode->Next = _Start;
            }
            _Start = newNode;
            ++_Count;
            ClearCache();
        }

        /// @brief 在任意位置添加数据
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @param value 值
        void Base_Add(int index, T value)
        {
            LimitIndex(index);
            if (index == 0)
            {
                Base_InsertAtFirst(value);
            }
            else if (index >= _Count)
            {
                Base_InsertAtLast(value);
            }
            else
            {
                Node<T> *insertAfter = GetNode(index - 1);
                Node<T> *newNode = new Node<T>(value);
                newNode->Preview = insertAfter;
                newNode->Next = insertAfter->Next;
                insertAfter->Next->Preview = newNode; // 因为在结尾插入的情况不会在这里出现，所以 insertAfter->Next 不会是 nullptr, 无需判空
                insertAfter->Next = newNode;
                ++_Count;
                ClearCache();
            }
        }

        /// @brief 移除任意位置的元素, 并返回被移除的值, 方便在构建 Queue 或者 Stack 时使用
        /// @param index // 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @return // 移除的值
        T Base_RemoveAt(int index)
        {
            Node<T> *node = GetNode(index);
            T value;
            if (node != nullptr)
            {
                value = node->Value;
                RemoveNode(node);
            }
            return value;
        }

        /// @brief 移除第一个元素, 方便在构建 Queue 时使用
        void Base_RemoveFirst()
        {
            RemoveNode(_Start);
        }

        /// @brief 移除最后一个元素, 方便在构建 Queue 或者 Stack 时使用
        void Base_RemoveLast()
        {
            RemoveNode(_End);
        }

        /// @brief 根据位置获取节点地址
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @return 节点地址
        Node<T> *GetNode(int index)
        {
            LimitIndex(index);

            // 被注释掉的是不使用 Cache 的方法, 即只以 _Start 或 _End 作为查找的起点
            // int moveTimes = index;
            // if (index > (_Count >> 1)) // 反向查找
            // {
            //     moveTimes = index - _Count;
            //     _NodeCache= GetNode_Reserved(moveTimes, _End);
            // }
            // else
            // {
            //     _NodeCache= GetNode_Forward(moveTimes, _Start);
            // }

            int diff_IndexAndCache = index - _NodeCacheIndex;
            bool fromR = index >= (_Count >> 1);
            int beginIndex = fromR ? _Count - 1 : 0;
            int diff_IndexAndBegin = index - beginIndex;
            Node<T> *beginNode;
            int moveTimes;
            if (_NodeCache != nullptr && (_Boolean::Math::Abs(diff_IndexAndCache) < _Boolean::Math::Abs(diff_IndexAndBegin))) // 有 Cache 且 目标位置距离 Cache 更近, 则从 Cache 开始查找
            {
                beginNode = _NodeCache;
                moveTimes = diff_IndexAndCache;
            }
            else
            {
                beginNode = fromR ? _End : _Start;
                moveTimes = diff_IndexAndBegin;
            }
            // qDebug()
            //     << "index" << index << " | "
            //     << "beginIndex" << beginIndex << " | "
            //     << "_NodeCache NULL" << (_NodeCache == nullptr) << " | "
            //     << "beginIndex" << beginIndex << " | "
            //     << "diff_IndexAndBegin" << diff_IndexAndBegin << " | "
            //     << "diff_IndexAndCache" << diff_IndexAndCache << " | "
            //     << "from" <<((beginNode == _NodeCache) ? "Cache" : ((beginNode == _Start) ? "_Start" : ((beginNode == _End) ? "_End" : "UNK"))) << " | "
            //     << "moveTimes" <<moveTimes;
            _NodeCache = moveTimes >= 0 ? GetNode_Forward(beginNode, moveTimes) : GetNode_Reserved(beginNode, moveTimes);

            _NodeCacheIndex = index;
            return _NodeCache;
        }

        /// @brief 移除并从内存中删除节点
        /// @param node 节点地址
        void RemoveNode(const Node<T> *node)
        {
            if (node == nullptr)
            {
                return;
            }
            Node<T> *nodeLeft = node->Preview;
            Node<T> *nodeRight = node->Next;
            if (nodeLeft != nullptr)
            {
                nodeLeft->Next = nodeRight;
            }
            else
            {
                _Start = nodeRight;
            }
            if (nodeRight != nullptr)
            {
                nodeRight->Preview = nodeLeft;
            }
            else
            {
                _End = nodeLeft;
            }
            --_Count;
            delete node;
            ClearCache();
        }

    private:
        Node<T> *_Start = nullptr;
        Node<T> *_End = nullptr;
        size_t _Count = 0;

        /// @brief 正方向查找
        /// @param node // 起始节点
        /// @param moveTimes 从起始节点移动的次数
        /// @return 查找到的节点
        Node<T> *GetNode_Forward(Node<T> *node, int &moveTimes) // index 为正数
        {
            while (moveTimes--)
            {
                node = node->Next;
            }
            return node;
        }

        /// @brief 反方向查找
        /// @param node // 起始节点
        /// @param moveTimes 从起始节点移动的次数
        /// @return 查找到的节点的地址
        Node<T> *GetNode_Reserved(Node<T> *node, int &moveTimes) // index 应为负数
        {
            while (moveTimes++)
            {
                node = node->Preview;
            }
            return node;
        }
    };

    template <typename T>
    class List : public Base<T>
    {
    public:
        List() : Base<T>() {};

        /// @brief 初始化并使用花括号添加多个变量
        /// @param values 若干初始值
        List(std::initializer_list<T> values)
        {
            for (const T *beg = values.begin(); beg != values.end(); ++beg)
            {
                Base<T>::Base_InsertAtLast(*beg);
            }
        };

        /// @brief 查找任意位置的值
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @return 值
        T At(int index) { return *Base<T>::Base_At(index); }

        /// @brief 追加值
        /// @param value 值
        void Append(T value) { Base<T>::Base_InsertAtLast(value); }

        /// @brief 在表开始位置添加值
        /// @param value 值
        void InsertAtFirst(T value) { Base<T>::Base_InsertAtFirst(value); }

        /// @brief 在任意位置插入值
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @param value 值
        void Insert(int index, T value) { Base<T>::Base_Add(index, value); }

        /// @brief 删除任意位置的值
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        void RemoveAt(int index) { Base<T>::Base_RemoveAt(index); }

        /// @brief 移除表中第一个值
        void RemoveFirst() { Base<T>::Base_RemoveFirst(); }

        /// @brief 移除表中最后一个值
        void RemoveLast() { Base<T>::Base_RemoveLast(); }

        /// @brief 获取任意位置节点的地址
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @return 节点的地址
        const _Boolean::Collections::Linked::Node<T> *const Node(int index) { return Base<T>::GetNode(index); }

        /// @brief 删除节点
        /// @param node 节点的地址
        void RemoveNode(const _Boolean::Collections::Linked::Node<T> *const node) { return Base<T>::RemoveNode(node); }

        /// @brief 修改任意位置的值
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @param newValue 新值
        /// @return 成功
        bool SetValue(int index, T newValue)
        {
            T *valuePtr = Base<T>::Base_At(index);
            if (valuePtr != nullptr)
            {
                *valuePtr = newValue;
                return true;
            }
            return false;
        }

        /// @brief 索引运算符, 不可作为左值, 若希望修改值请使用 SetValue()
        /// @param index 位置, 可取任意实数, 查找时会被限制在 [-Length, Length) 区间内, 负值则是反向查找
        /// @return 值
        T &operator[](int index)
        {
            return *Base<T>::Base_At(index);
        }
    };
}

#endif
