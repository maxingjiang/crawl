//
// chat_server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//服务器端程序，首先开启一个chat_server，用来初始话io_service和chat_room;  服务器每次只开启一个chat_room，chat_room的作用是 1//.保存用户信息  2.实现用户的join和leave  3.保存从每个客户端接收到的信息  4.将接收到的消息挂到每一个客户端write_msgs队尾
//每连接上一个客户端（socket）就开启一个新的chat_session 并加入唯一的chat_room   chat_session中实现分别对每一个客户端的异步读写//操作

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>
#include "getDataFromUrl.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include "chat_message.hpp"
#include <vector>
#include "businfo.h"

using boost::asio::ip::tcp;

//----------------------------------------------------------------------

typedef std::deque<chat_message> chat_message_queue;

//----------------------------------------------------------------------

class chat_participant
{
public:
  virtual ~chat_participant() {}
  virtual void deliver(const chat_message& msg) = 0; //后面需要重载
};

typedef boost::shared_ptr<chat_participant> chat_participant_ptr;

//----------------------------------------------------------------------

class chat_room
{
public:
  void join(chat_participant_ptr participant)
  {
	//std::cout<<"join: "<<std::endl;
    participants_.insert(participant);
    std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
        boost::bind(&chat_participant::deliver, participant, _1));
  }

  void leave(chat_participant_ptr participant)
  {
    participants_.erase(participant);
  }


//将从某个客户端收到的消息挂到 每一个客户端的write_msgs队尾 具体见chat_participant::deliver

  void deliver(const chat_message& msg)

  {
	//std::cout<<"chat_room deliver: "<<std::endl;
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
        recent_msgs_.pop_front(); //room中保存的消息数有限

    std::for_each(participants_.begin(), participants_.end(),
        boost::bind(&chat_participant::deliver, _1, boost::ref(msg)));
  }

private:
  std::set<chat_participant_ptr> participants_;//用set来保存用户信息
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;//用来保存从某个客户端接收到的信息
};

//----------------------------------------------------------------------

class chat_session
  : public chat_participant,
    public boost::enable_shared_from_this<chat_session>
{
public:
  chat_session(boost::asio::io_service& io_service, chat_room& room)
    : socket_(io_service),
      room_(room)
  {
  }

  tcp::socket& socket()
  {
    return socket_;
  }

  void start()//每生成一个新的chat_session都会调用
  {
	//std::cout<<"start: "<<std::endl;
    room_.join(shared_from_this());
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), chat_message::header_length),
        boost::bind(
          &chat_session::handle_read_header, shared_from_this(),
          boost::asio::placeholders::error)); //异步读客户端发来的消息
  }

  void deliver(const chat_message& msg)
  {
	//std::cout<<"chat_session deliver: "<<std::endl;
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg); //把room中保存的消息挂到write_msgs队尾
    if (!write_in_progress)
    {
	  std::cout<<"send: "<<write_msgs_.front().data()<<std::endl;
	  //std::cout<<"send data:"<<write_msgs_.front().data()+4<<":"<<write_msgs_.front().length()<<std::endl;
/*
      boost::asio::async_write(socket_,
    		  boost::asio::buffer(write_msgs_.front().data(),
            write_msgs_.front().length()),
          boost::bind(&chat_session::handle_write, shared_from_this(),
            boost::asio::placeholders::error));*/
	  businfo bus;
	  string src = write_msgs_.front().data()+4;
	  LineIdAndTerminusId ids = bus.getLineIdAndTerminusId(src);
	  CURL *curl;
	  vector<busPositionInfo> busPositionInfos = server_run(curl, ids.lineID, ids.terminusId);
	  cout<<"busPositionInfos size()=====>"<<busPositionInfos.size()<<endl;

	  cout<<": jsondata==for===>"<<endl;
	  string jsonsrc = bus.setJsonSrcs(busPositionInfos);
	  int jsonsrc_len = jsonsrc.length();
	  char header[6];
	  sprintf(header, "%4d", jsonsrc_len);
	  string jsondata = header + jsonsrc;
	  cout<<": jsondata=====>"<<jsondata<<endl;
	  boost::asio::async_write(socket_,
	      		  boost::asio::buffer(jsondata, jsonsrc_len + 4),
	            boost::bind(&chat_session::handle_write, shared_from_this(),
	              boost::asio::placeholders::error));

    }
  }

  void handle_read_header(const boost::system::error_code& error)
  {
    if (!error && read_msg_.decode_header())
    {
	  //std::cout<<"handle_read_header: "<<read_msg_.data()<<" : "<<chat_message::header_length<<std::endl;
	 // std::cout.write(read_msg_.data(), chat_message::header_length); //输出消息
	  //std::cout<<std::endl;
      boost::asio::async_read(socket_,
          boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
          boost::bind(&chat_session::handle_read_body, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      room_.leave(shared_from_this());
    }
  }

  void handle_read_body(const boost::system::error_code& error)
  {
    if (!error)
    {
	  //std::cout<<"handle_read_body: "<<read_msg_.body()<<" : "<<read_msg_.body_length()<<std::endl;
      room_.deliver(read_msg_);
      boost::asio::async_read(socket_,
          boost::asio::buffer(read_msg_.data(), chat_message::header_length),
          boost::bind(&chat_session::handle_read_header, shared_from_this(),
            boost::asio::placeholders::error));
    }
    else
    {
      room_.leave(shared_from_this());
    }
  }

  void handle_write(const boost::system::error_code& error)
  {
	//std::cout<<"=======handle_write: "<<write_msgs_.front().data()<<std::endl;
    if (!error)
    {
      write_msgs_.pop_front();
      //std::cout<<"=======handle_write error: "<<write_msgs_.empty()<<std::endl;
      if (!write_msgs_.empty())
      {
        boost::asio::async_write(socket_,
            boost::asio::buffer(write_msgs_.front().data(),
              write_msgs_.front().length()),
            boost::bind(&chat_session::handle_write, shared_from_this(),
              boost::asio::placeholders::error)); //服务器端将收到的消息送给所有的客户端（广播的方式）
      }
    }
    else
    {
      room_.leave(shared_from_this());
    }
  }

private:
  tcp::socket socket_;
  chat_room& room_;
  chat_message read_msg_;
  chat_message_queue write_msgs_;
};

typedef boost::shared_ptr<chat_session> chat_session_ptr;

//----------------------------------------------------------------------

class chat_server
{
public:
  chat_server(boost::asio::io_service& io_service,
      const tcp::endpoint& endpoint)
    : io_service_(io_service),
      acceptor_(io_service, endpoint) //全局只有一个io_service和一个acceptor
  {
	  //std::cout<<"chat_server: "<<std::endl;
      start_accept();
  }

  void start_accept()
  {
	//std::cout<<"start_accept: "<<std::endl;
    chat_session_ptr new_session(new chat_session(io_service_, room_));
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&chat_server::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(chat_session_ptr session,
      const boost::system::error_code& error)
  {
    if (!error)
    {
    	//std::cout<<"handle_accept: "<<std::endl;
        session->start();
    }

    start_accept(); //每连接上一个socket都会调用
  }

private:
  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
  chat_room room_; //chat_room中没有重载构造函数 所以会直接调用默认构造函数
};

typedef boost::shared_ptr<chat_server> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

//----------------------------------------------------------------------

int main(int argc, char* argv[])
{
  try
  {
	curl_global_init(CURL_GLOBAL_ALL);
    if (argc < 2)
    {
      std::cerr << "Usage: server <port> [<port> ...]\n";
      return 1;
    }

    boost::asio::io_service io_service;

    chat_server_list servers;
    for (int i = 1; i < argc; ++i)
    {
      using namespace std; // For atoi.
      tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
      chat_server_ptr server(new chat_server(io_service, endpoint));
      servers.push_back(server);
    }

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  curl_global_cleanup();
  return 0;
}
