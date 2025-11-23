pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Building...'
                // Компілюємо програму (sh замість bat)
                sh 'g++ main.cpp -o my_program'
            }
        }
        stage('Test') {
            steps {
                echo 'Testing...'
                // Запускаємо програму
                sh './my_program'
            }
        }
    }
}