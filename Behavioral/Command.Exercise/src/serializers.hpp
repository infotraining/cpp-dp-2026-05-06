#ifndef SERIALIZERS_HPP
#define SERIALIZERS_HPP

template <typename TStream>
class StreamOutputSerializer
{
    TStream& out_stream_;

public:
    StreamOutputSerializer(TStream& out_stream)
        : out_stream_{out_stream}
    { }

    template <typename... TArgs>
    bool operator()(const TArgs&... args)
    {
        ((out_stream_ << args), ...);
        return !out_stream_.fail();
    }
};

template <typename TStream>
class StreamInputSerializer
{
    TStream& in_stream_;

public:
    StreamInputSerializer(TStream& out_stream)
        : in_stream_{out_stream}
    { }

    template <typename... TArgs>
    bool operator()(TArgs&... args)
    {
        ((in_stream_ >> args), ...);
        return !in_stream_.fail();
    }
};

#endif