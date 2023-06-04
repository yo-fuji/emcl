# launchサンプル

[navigation2パッケージ](https://github.com/ros-planning/navigation2.git)の
[localization_launch.py](https://github.com/ros-planning/navigation2/blob/main/nav2_bringup/launch/localization_launch.py)において、
amclをemclに置換する手順を示します。

1. lifecycle_nodesのamclをemclに置換します。
    * 修正前
        ```
        lifecycle_nodes = ['map_server', 'amcl']
        ```
    * 修正後
        ```
        lifecycle_nodes = ['map_server', 'emcl']
        ```

2. load_nodesのamclをemclで置換します。
    * 修正前
        ```
        Node(
            package='nav2_amcl',
            executable='amcl',
            name='amcl',
            output='screen',
            respawn=use_respawn,
            respawn_delay=2.0,
            parameters=[configured_params],
            arguments=['--ros-args', '--log-level', log_level],
            remappings=remappings),
        ```
    * 修正後
        ```
        Node(
            package='emcl',
            executable='emcl_node',
            name='emcl',
            output='screen',
            respawn=use_respawn,
            respawn_delay=2.0,
            parameters=[configured_params],
            arguments=['--ros-args', '--log-level', log_level],
            remappings=remappings),
        ```

3. load_composable_nodesのamclをemclに置換します。
    * 修正前
        ```
        ComposableNode(
            package='nav2_amcl',
            plugin='nav2_amcl::AmclNode',
            name='amcl',
            parameters=[configured_params],
            remappings=remappings),
        ```
    * 修正後
        ```
        ComposableNode(
            package='emcl',
            plugin='emcl::EMclNode',
            name='emcl',
            parameters=[configured_params],
            remappings=remappings),
        ```

4. [nav2_params.yaml](https://github.com/ros-planning/navigation2/blob/main/nav2_bringup/params/nav2_params.yaml)のamcl設定をemclに置換します。
    * 修正前
        ```
        amcl:
            ros__parameters:
                alpha1: 0.2
                alpha2: 0.2
                alpha3: 0.2
                alpha4: 0.2
                alpha5: 0.2
                (以下省略)
        ```
    * 修正後
        ```
        emcl:
            ros__parameters:
                odom_freq: 20
                num_particles: 500
                odom_frame_id: "odom"
                footprint_frame_id: "base_footprint"
                base_frame_id: "base_link"
                odom_fw_dev_per_fw: 0.19
                odom_fw_dev_per_rot: 0.0001
                odom_rot_dev_per_fw: 0.13
                odom_rot_dev_per_rot: 0.2
                laser_likelihood_max_dist: 0.2
                alpha_threshold: 0.6
                open_space_threshold: 0.05
                expansion_radius_position: 0.1
                expansion_radius_orientation: 0.2
                laser_min_range: 0.0
                laser_max_range: 100000000.0
                scan_increment: 1
        ```

5. [package.xml](https://github.com/ros-planning/navigation2/blob/main/nav2_bringup/package.xml)の依存パッケージにemclを追加します。
    * 追加
        ```
        <exec_depend>emcl</exec_depend>
        ```
