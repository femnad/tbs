tbs
===

tbs: Tmux buffer sync

Why and How Come?
=================

So that one day one may be able to peruse Tmux buffer on remote server to their
heart's content.

Usage
=====

On the remote server, run `tbs_server`. In your Tmux configuration, bind a key
for committing the unspeakable act:

    bind-key z run "tmux show-buffer > /tmp/tbs"

which only writes the last item of Tmux's buffer to a FIFO created by the
aforementioned executable. Lastly have the `tbs_client` running on the local
computer which will get the updates to the remote server's tmux buffer list.

Requirements
============

* libzmq [https://github.com/zeromq/libzmq]
* czmq [https://github.com/zeromq/czmq]
