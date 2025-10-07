#include <iostream>
#include <client_logger_builder.h> 

int main()
{
    client_logger_builder * b1 = new client_logger_builder;

    logger* l1 = b1->transform_with_configuration(
        "..\\..\\logger_conf.json", "file_paths")
        ->add_console_stream(logger::severity::trace)
        ->add_console_stream(logger::severity::debug)
        ->add_console_stream(logger::severity::information)
        ->set_format("[%d %t] %s %m")
        ->build();

    delete b1;

    client_logger_builder * b2 = new client_logger_builder;

    logger* l2 = b2->transform_with_configuration(
        "..\\..\\logger_conf.json", "file_paths")
        ->add_console_stream(logger::severity::trace)
        ->add_console_stream(logger::severity::debug)
        ->add_console_stream(logger::severity::information)
        ->set_format("[%d %t] %s %m")
        ->build();

    delete b2;

    l1->log("test1", logger::severity::trace);

    l2->log("test2", logger::severity::debug);

    delete l1;

    l2->log("test3", logger::severity::information);

    delete l2;

    return 0;
}