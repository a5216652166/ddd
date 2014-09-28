#!/usr/bin/env python
# -*- coding:UTF-8 -*-
# made by likunxiang

import threading
import Queue
import sys
import time
__all__ = ['Qthread']

class Qthread(threading.Thread):

    def __init__(self, name, qsize):
        threading.Thread.__init__(self)
        self.thread_stop = False
        self.th_name = name
        self.tq = Queue.Queue(qsize)
        self.log_queue = False
        self.lock = threading.Lock()

    def get_queue():
        return self.tq

    def put(self, data):
        while True:
            self.lock.acquire()
            if self.tq.full():
                self.lock.release()
                print 'queue full go to sleep'
                time.sleep(1)
            else:
                break

        self.tq.put(data, block=False)
        self.lock.release()

    def run(self):
        while not self.thread_stop:
            try:
                data = self.tq.get(block=True, timeout=1)
                if self.thread_stop:
                    self.tq.task_done()
                    break
                self.handler(data)
                self.tq.task_done()
            except Queue.Empty as e:
                if self.log_queue:
                    print ('[',
                     self.th_name,
                     ':run] taskq is ',
                     repr(e))
            except Exception as e:
                self.tq.task_done()
                print ('[',
                 self.th_name,
                 ':run] inner error:',
                 repr(e))

        self.onstop()

    def handler(self, data):
        pass

    def stop(self):
        self.thread_stop = True

    def onstop(self):
        pass
