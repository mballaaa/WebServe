

#ifndef RESPONSE_HPP
#define RESPONSE_HPP
class Http_req;
class Response
{
    private:
        //Http_req objec;

    public:
        Response( );
        void Methode( Http_req &obj);
        void LetGet();
};


#endif