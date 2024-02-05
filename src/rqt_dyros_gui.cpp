#include "rqt_dyros_gui/rqt_dyros_gui.h"
#include <pluginlib/class_list_macros.hpp>
#include <QStringList>

namespace rqt_dyros_gui
{

  RqtDyrosPlugin::RqtDyrosPlugin()
      : rqt_gui_cpp::Plugin(), widget_(0)
  {
    TOTALDOF = 6;
    // Constructor is called first before initPlugin function, needless to say.

    // give QObjects reasonable names
    setObjectName("RqtDyrosPlugin");
  }

  void RqtDyrosPlugin::initPlugin(qt_gui_cpp::PluginContext &context)
  {
    // access standalone command line arguments
    QStringList argv = context.argv();
    // create QWidget
    widget_ = new QWidget();
    // extend the widget with all attributes and children from UI file
    ui_.setupUi(widget_);
    // add widget to the user interface
    context.addWidget(widget_);
    bool real_robot = true;
    // rclcpp::Parameter::get_value("real", real_robot);
    // mySub = node_->create_subscription<std_msgs::msg::Float32>("sub", 100, std::bind(&RqtDyrosPlugin::subCallback, this, std::placeholders::_1));
    if(real_robot == true)
    {
      jointstatesReal_Sub = node_->create_subscription<sensor_msgs::msg::JointState>("motor/joint_states", 100, std::bind(&RqtDyrosPlugin::realSubCallback, this, std::placeholders::_1));
    }
    else
    {
      jointstates_Sub = node_->create_subscription<sensor_msgs::msg::JointState>("joint_states", 100, std::bind(&RqtDyrosPlugin::subCallback, this, std::placeholders::_1));
    }
  
    connect(ui_.SendButton, SIGNAL(clicked()), this, SLOT(sendbutton()));
    connect(ui_.SendInitButton, SIGNAL(clicked()), this, SLOT(sendinitbutton()));
    connect(ui_.EMSTOP, SIGNAL(clicked()), this, SLOT(sendemstop()));
    connect(ui_.Start, SIGNAL(clicked()), this, SLOT(sendstart()));

    myParam = node_->create_publisher<std_msgs::msg::Float32MultiArray>("guiparam", 1);
    myCommand = node_->create_publisher<std_msgs::msg::String>("commanding", 1);
    exec_pub_ = node_->create_publisher<std_msgs::msg::Float32>("exec_time", 1);
  }

void RqtDyrosPlugin::sendbutton()
  {
    std_msgs::msg::Float32MultiArray data_msg;
    std_msgs::msg::Float32 time_msg;

    data_msg.data.push_back(0);
    data_msg.data.push_back(0);
    data_msg.data.push_back(0);
    data_msg.data[0] = ui_.lineEdit_6->text().toFloat();
    data_msg.data[1] = ui_.lineEdit_7->text().toFloat();
    data_msg.data[2] = ui_.lineEdit_8->text().toFloat();
    time_msg.data = ui_.Exec_Time->text().toFloat();

    myParam->publish(data_msg);
    exec_pub_->publish(time_msg);
  }

  void RqtDyrosPlugin::sendinitbutton()
  {
    std_msgs::msg::String msg;
    msg.data = "initpose";
    myCommand->publish(msg);
  }

  void RqtDyrosPlugin::sendemstop()
  {
    std_msgs::msg::String msg;
    msg.data = "em";
    myCommand->publish(msg);
  }

  void RqtDyrosPlugin::sendstart()
  {
    std_msgs::msg::String msg;
    msg.data = "start";
    myCommand->publish(msg);
  }

  void RqtDyrosPlugin::subCallback(const sensor_msgs::msg::JointState msg)
  {
    // std::cout << "subcallback" << std::endl;
    ui_.lineEdit_0->setText(QString::number(rad2deg(msg.position[0])));
    ui_.lineEdit_1->setText(QString::number(rad2deg(msg.position[1])));
    ui_.lineEdit_2->setText(QString::number(rad2deg(msg.position[2])));
    ui_.lineEdit_3->setText(QString::number(rad2deg(msg.position[3])));
    ui_.lineEdit_4->setText(QString::number(rad2deg(msg.position[4])));
    ui_.lineEdit_5->setText(QString::number(rad2deg(msg.position[5])));
  }

  void RqtDyrosPlugin::realSubCallback(const sensor_msgs::msg::JointState msg)
  {
    // std::cout << "subcallback" << std::endl;
    ui_.lineEdit_0->setText(QString::number(rad2deg(msg.position[0])));
    ui_.lineEdit_1->setText(QString::number(rad2deg(msg.position[1])));
    ui_.lineEdit_2->setText(QString::number(rad2deg(msg.position[2])));
    ui_.lineEdit_3->setText(QString::number(rad2deg(msg.position[3])));
    ui_.lineEdit_4->setText(QString::number(rad2deg(msg.position[4])));
    ui_.lineEdit_5->setText(QString::number(rad2deg(msg.position[5])));
  }


  void RqtDyrosPlugin::shutdownPlugin()
  {
    // TODO unregister all publishers here
  }

  void RqtDyrosPlugin::saveSettings(qt_gui_cpp::Settings &plugin_settings, qt_gui_cpp::Settings &instance_settings) const
  {
    (void)plugin_settings;

    // TODO save intrinsic configuration, usually using:
    // instance_settings.setValue(k, v)
  }

  void RqtDyrosPlugin::restoreSettings(const qt_gui_cpp::Settings &plugin_settings, const qt_gui_cpp::Settings &instance_settings)
  {
    (void)plugin_settings;

    // TODO restore intrinsic configuration, usually using:
    // v = instance_settings.value(k)
  }

  /*bool hasConfiguration() const
  {
    return true;
  }

  void triggerConfiguration()
  {
    // Usually used to open a dialog to offer the user a set of configuration
  }*/

} // namespace

PLUGINLIB_EXPORT_CLASS(rqt_dyros_gui::RqtDyrosPlugin, rqt_gui_cpp::Plugin)