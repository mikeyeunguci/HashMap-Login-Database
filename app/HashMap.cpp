#include "HashMap.hpp"
#include <iostream>
#include "HashFunction.hpp"

void HashMap::DeleteHashMap(Node** buckets_del, unsigned int size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        Node* current = buckets_del[i];
        while (current != nullptr)
        {
            Node* to_del = current;
            current = current->next;
            delete to_del;
        }
    }
    delete[] buckets_del;
}


void HashMap::CopyHashMap(Node** target, Node** source, unsigned int capacity)
{
    for (unsigned int i = 0; i < capacity; ++i)
    {
        Node* current = source[i];
        Node** copycurrent = &target[i];
        *copycurrent = nullptr;
        while (current != nullptr)
        {
            Node* copyNode = new Node{current->key, current->value, nullptr};
            *copycurrent = copyNode;
            copycurrent = &copyNode->next;
            current = current->next;
        }
    }
}


void HashMap::reHash()
{
    unsigned int prevcap = cap;
    cap = cap * 2 + 1;
    sz = 0;
    Node** newBuckets = NewBuckets(cap); 
    Node** copy_buckets = buckets;
    buckets = newBuckets;
    for (unsigned int i = 0; i < prevcap; ++i)
    {
        Node* current = copy_buckets[i];
        while (current != nullptr)
        {
            add(current->key, current->value);
            current = current->next;
        }
    }
    DeleteHashMap(copy_buckets, prevcap); 
}


HashMap::Node** HashMap::NewBuckets(unsigned int capacity)
{
    Node** Newbucket = new Node*[capacity];
    for (unsigned int i = 0; i < capacity; i++)
    {
        Newbucket[i] = nullptr;
    }
    return Newbucket;
}


HashMap::HashMap()
    :hashFunction{hash}, buckets{NewBuckets(INITIAL_BUCKET_COUNT)}, sz{0}, cap{INITIAL_BUCKET_COUNT}
{
}


HashMap::HashMap(HashFunction hashFunction)
    :hashFunction{hashFunction}, buckets{NewBuckets(INITIAL_BUCKET_COUNT)}, sz{0}, cap{INITIAL_BUCKET_COUNT}
{
}


HashMap::HashMap(const HashMap& hm)
    :hashFunction{hm.hashFunction}, buckets{new Node* [hm.cap]}, sz{hm.sz}, cap{hm.cap}
{
    CopyHashMap(buckets, hm.buckets, cap);
}


HashMap::~HashMap()
{
    for (unsigned int i = 0; i < cap; ++i)
    {
        Node* current = buckets[i];
        while (current != nullptr)
        {
            Node* to_del = current;
            current = current->next;
            delete to_del;
        }
    }
    delete[] buckets;
}


HashMap& HashMap::operator=(const HashMap& hm)
{
    if (this != &hm)
    {
        Node** newbuckets = new Node* [hm.cap];
        CopyHashMap(newbuckets, hm.buckets, hm.cap);
        hashFunction = hm.hashFunction;
        sz = hm.sz;
        cap = hm.cap;

        DeleteHashMap(buckets, cap); 
        buckets = newbuckets;
    }
    return *this;
}


void HashMap::add(const std::string& key, const std::string& value)
{
    if (!contains(key))
    {
        unsigned int hashvalue = hashFunction(key) % cap;
        Node* current = buckets[hashvalue];
        Node* prev = nullptr;
        while (current != nullptr)
        {
            prev = current;
            current = current->next;
        }
        if (prev == nullptr)
        {
            buckets[hashvalue] = new Node{key, value, nullptr};
            sz++;
        }
        else
        {
            prev->next = new Node{key, value, nullptr};
            sz++;
        }
    }

    if (loadFactor() > 0.8)
    {
        reHash();
    }
}


bool HashMap::remove(const std::string& key) 
{
    if (contains(key))
    {
        unsigned int hashvalue = hashFunction(key) % cap;
        Node* prev = nullptr;
        Node* current = buckets[hashvalue];
        while (current != nullptr)
        {
            if (current->key == key)
            {
                if (prev == nullptr)
                {
                    buckets[hashvalue] = current->next;
                    sz--;
                    delete current;
                    return true;
                }
                else
                {
                    prev->next = current->next;
                    sz--;
                    delete current;
                    return true;
                }
            }
            prev = current;
            current = current->next;
        }
    }
    return false;
}


bool HashMap::contains(const std::string& key) const
{
    unsigned int hashvalue = hashFunction(key) % cap;
    Node* current = buckets[hashvalue];
    while (current != nullptr)
    {
        if (current->key == key)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}


std::string HashMap::value(const std::string& key) const
{
    if (contains(key))
    {
        unsigned int hashvalue = hashFunction(key) % cap;
        Node* current = buckets[hashvalue];
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return current->value;
            }
            current = current->next;
        }
        
    }
    return "";
}


unsigned int HashMap::size() const
{
    return sz;
}


unsigned int HashMap::bucketCount() const // check meaning
{
    return cap;
}


double HashMap::loadFactor() const
{
    double sz_dbl = sz;
    double cap_dbl = cap;
    return sz_dbl / cap_dbl;
}


unsigned int HashMap::maxBucketSize() const
{
    unsigned int longestlen = 0;
    for (unsigned int i = 0; i < cap; ++i)
    {
        unsigned int len = 0;
        Node* current = buckets[i];
        while (current != nullptr)
        {
            len++;
            current = current->next;
        }
        if (len > longestlen)
        {
            longestlen = len;
        }
    }
    return longestlen;
}


void HashMap::clear() 
{
    for (unsigned int i = 0; i <  cap; ++i)
    {
        Node* current = buckets[i];
        while (current != nullptr)
        {
            Node* prev = current;
            current = current->next;
            delete prev;
        }
        buckets[i] = nullptr;
    }
    sz = 0;
}


void HashMap::PrintAll()
{
    std::cout << "Printing HashMap Bucket_Index, Key, Value" << std::endl;
    for (unsigned int i = 0; i < cap; ++i)
    {
        Node* current = buckets[i];
        while (current != nullptr)
        {
            std::cout << i << " " << current->key << " " << current->value << std::endl;
            current = current->next;
        }
    }
}