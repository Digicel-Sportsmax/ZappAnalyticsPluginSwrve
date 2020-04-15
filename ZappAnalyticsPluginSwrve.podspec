Pod::Spec.new do |s|

    s.name             = "ZappAnalyticsPluginSwrve"
    s.version          = '0.0.3'
    s.summary          = "ZappAnalyticsPluginSwrve analytics plugin for Zapp iOS."
    s.description      = <<-DESC
                          ZappAnalyticsPluginSwrve analytics plugin for Zapp iOS.
                         DESC
    s.homepage         = "https://github.com/mohieddinezarif/ZappAnalyticsPluginSwrve"
    s.license          = 'MIT'
    s.author           = { "Mohieddine Zarif" => "mohieddine.zarif@gotocme.com" }
    s.source           = { :git => "git@github.com:mohieddinezarif/ZappAnalyticsPluginSwrve.git", :tag => s.version.to_s }
  
    s.ios.deployment_target  = "10.0"
    s.platform     = :ios, '10.0'
    s.requires_arc = true
    s.swift_version = '5.1'

    s.subspec 'Core' do |c|
      s.resources = []
      c.frameworks = 'UIKit'
      c.source_files = 'PluginClasses/*.{swift,h,m}'
      c.dependency 'ApplicasterSDK'
      c.dependency 'ZappPlugins'
      c.dependency 'ZappAnalyticsPluginsSDK'
      c.dependency 'SwrveSDK'
    end
                  
  s.xcconfig =  { 'CLANG_ALLOW_NON_MODULAR_INCLUDES_IN_FRAMEWORK_MODULES' => 'YES',
                  'ENABLE_BITCODE' => 'YES',
                  'SWIFT_VERSION' => '5.1'
                }
                  
    s.default_subspec = 'Core'
                  
  end
  