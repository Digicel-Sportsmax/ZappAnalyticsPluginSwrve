platform :ios, '10.0'
use_frameworks!
install! 'cocoapods', :deterministic_uuids => false

source 'git@github.com:applicaster/CocoaPods.git'
source 'git@github.com:applicaster/PluginsBuilderCocoaPods.git'
source 'git@github.com:CocoaPods/Specs.git'

def shared_pods
  pod 'ZappPlugins'
  pod 'ApplicasterSDK'
  pod 'SwrveSDK'
end

target 'ZappAnalyticsPluginSwrve' do
    pod 'ZappAnalyticsPluginSwrvePlugin', :path => 'ZappAnalyticsPluginSwrve.podspec'
    shared_pods
end

post_install do |installer|
    installer.pods_project.targets.each do |target|
        target.build_configurations.each do |config|
            config.build_settings['SWIFT_VERSION'] = '5.1'
        end
    end
end

pre_install do |installer|
    # workaround for https://github.com/CocoaPods/CocoaPods/issues/3289
    Pod::Installer::Xcode::TargetValidator.send(:define_method, :verify_no_static_framework_transitive_dependencies) {}
end