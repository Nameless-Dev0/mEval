## Token stream test cases

 & destruction
- Append tokens & check current
- Buffer resize on append
- Iterating tokens

- Pass NULL token to stream_append_token
- Pass NULL stream to:
    - stream_destroy,
    - stream_curr_token,
    - stream_iterate_token,
    - stream_append_token

### Stream creation
- Pass numerical max size_t
- Pass numerical max size_t
