// problem: https://leetcode.com/problems/lru-cache/

class Node {
  public:
    Node * prev;
    Node * next;
    int value;
    bool incl;
    Node(int value) {
      prev = NULL;
      next = NULL;
      this->value = value;
      incl = false;
    }
};

class LRUQ {
  public:
    Node * head;
    Node * tail;
    int size;
    LRUQ() {
      head = NULL;
      tail = NULL;
      size = 0;
    }

    void del(Node * node) {
      if (node->prev != NULL)
        node->prev->next = node->next;
      else
        head = node->next;

      if (node->next != NULL)
        node->next->prev = node->prev;
      else
        tail = node->prev;

      node->incl = false;

      size--;
    }

    void front(Node * node) {
      if (node == head) return;
      if (head == NULL) { head = node; return; }
      // cout << "before front(" << node->value << "): ";
      del(node);
      size++;
      node->prev = NULL;
      node->next = head;
      node->incl = true;
      head->prev = node;
      head = node;
      if (node->next == NULL)
        tail = node;
      // cout << "after front(" << node->value << "): ";
    }

    void append(Node * node) {
      if (tail != NULL)
        tail->next = node;
      node->prev = tail;
      tail = node;
      node->incl = true;
      size++;
    }

    void evict() {
      del(tail);
    }
};

class LRUCache {
  public:
    int cap;
    Node ** nodes;
    LRUQ * q;

    LRUCache(int capacity) {
      cap = capacity;
      int tsize = 1000 * capacity;
      nodes = new Node*[tsize];
      for (int i = 0; i < tsize; i++)
        nodes[i] = new Node(-1);

      q = new LRUQ();
    }

    int get(int key) {
      Node * node = nodes[key];
      if (! node->incl) return -1;
      q->front(node);
      return node->value;
    }

    void put(int key, int value) {
      // if key missing from cache
      Node * node = nodes[key];
      node->value = value;

      if (node->incl) q->front(node);
      else {
        // if full evict
        if (q->size == cap)
          q->evict();

        q->append(node);
        q->front(node);
      }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
