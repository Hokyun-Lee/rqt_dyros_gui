#ifndef RQT_DYROS_H
#define RQT_DYROS_H

#include <rqt_gui_cpp/rqt_gui_cpp/plugin.h>
#include <ui_rqt_dyros_gui.h>
#include <QWidget>

#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float32_multi_array.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <iostream>

#define PI 3.14159265359
#define deg2rad(deg)  ((deg) * PI / 180.0)
#define rad2deg(rad)  ((rad) * 180.0 / PI)

namespace rqt_dyros_gui {

class RqtDyrosPlugin
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  RqtDyrosPlugin();
  int TOTALDOF;
  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

  void subCallback(const sensor_msgs::msg::JointState msg);
  void realSubCallback(const sensor_msgs::msg::JointState msg);
  

protected slots:
  virtual void sendbutton();
  virtual void sendinitbutton();
  virtual void sendemstop();
  virtual void sendstart();


//signals:
  // Comment in to signal that the plugin has a way to configure it
  //bool hasConfiguration() const;
  //void triggerConfiguration();

private:
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr jointstates_Sub;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr jointstatesReal_Sub;
  rclcpp::Publisher<std_msgs::msg::Float32MultiArray>::SharedPtr myParam;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr myCommand;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr exec_pub_;
  Ui::RqtDyrosGuiWidget ui_;
  QWidget* widget_;
};
} // namespace

#endif // my_namespace__my_plugin_H
